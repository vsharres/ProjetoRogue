// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Door.h"
#include "ProtuXPlayer.h"
#include "RoomGenerator.h"
#include "EnemySpawnerComponent.h"

// Constructor
ARoom::ARoom(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Inicializando o trigger de ativação dos inimigos
	TriggerEnemiesActivate = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerAtivarInimigos"));
	TriggerEnemiesActivate->SetBoxExtent(FVector(300.0f, 300.0f, 32.0f));
	
	//Trigger é o componente raiz do ator.
	RootComponent = TriggerEnemiesActivate;
	
	//Inicializando propriedades.
	bCanBeDamaged = false;
	NumberDoors = ENumberDoors::ONE;
	RoomDirection = ERoomShape::STANDARD;
	RoomType = ERoomType::NORMAL;
	Difficulty = ERoomDifficulty::NORMAL;
	ConectedRooms.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	Doors.Empty();
	bVisited = false;
	bRoomHasEnemies = false;
	Enemies.Empty();
	RoomOffset = 6000.0f;
	RoomScale = FVector(1.0f, 1.0f, 1.0f);

}


void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Interface do Tick

	OnEnemiesDefeated(); //Checando se os inimigos foram derrotados

}

FVector ARoom::GetRoomScale()
{
	return RoomScale;
}

float ARoom::GetRoomOffset() const
{
	return RoomOffset;
}

ENumberDoors ARoom::GetNumDoors()
{
	return NumberDoors;
}

ERoomShape ARoom::GetRoomShape()
{
	return RoomDirection;
}

ERoomType ARoom::GetRoomType()
{
	return RoomType;
}

TArray<TEnumAsByte<EDoorDirection>> ARoom::GetArrayDoors()
{
	return DoorsDirArray;
}

void ARoom::SetOffset(float novoOffset)
{
	this->RoomOffset = novoOffset;
}

void ARoom::DeactivateTrigger()
{
	TriggerEnemiesActivate->OnComponentBeginOverlap.RemoveAll(this);
	TriggerEnemiesActivate->OnComponentEndOverlap.RemoveAll(this);
}

void ARoom::RemoveEnemy(AEnemy* enemy)
{
	if (enemy)
	{
		Enemies.Remove(enemy);
	}
}

void ARoom::SpawnEnemies_Implementation(FRandomStream& Stream)
{
	if (!bRoomHasEnemies)//Se a sala não tem inimigos, nao fazer o spawn.
		return;

	TInlineComponentArray<UEnemySpawnerComponent*> Components; 
	this->GetComponents(Components); //Encontrar todos os componentes de spawn no ator.

	TArray<TSubclassOf<AEnemy>> EnemyType; // Tipo do inimigo a ser feito spawn

	switch (Difficulty) //Escolher o inimigos baseado na dificuldade da sala.
	{
	case ERoomDifficulty::NORMAL:
		EnemyType = ListEnemiesNormal;
		break;
	case ERoomDifficulty::HARD:
		EnemyType = ListEnemiesHard;
		break;
	default:
		checkNoEntry();
		break;
	}

	for (const auto& Spawner : Components) //Para cada ponto de spawn, escolher um inimigo e fazer o spawn
	{
		AEnemy* newEnemy =  NULL;

		if (Spawner->bSpawnRandomly) 
		{
			//check(TipoInimigo.Num() > 0);
			if (Spawner->GetNumEnemies(Difficulty) > 0) //Garantir que nenhuma classe nula vai ser usada e que o ponto de spawn tem um tipo de inimigo especifico a ser usado.
			{
				//Spawn do inimigo randomicamente
				newEnemy = GetWorld()->SpawnActor<AEnemy>(Spawner->SelectEnemyRand(Stream,Difficulty), Spawner->GetComponentLocation(), FRotator::ZeroRotator); 
			}
			else //usando os inimigos da sala.
			{
				newEnemy = GetWorld()->SpawnActor<AEnemy>(GetEnemyType(EnemyType,Stream), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}
		else
		{
			TSubclassOf<AEnemy> NonRandEnemyClass;
			

			switch (Difficulty) //Escolher o inimigos baseado na dificuldade da sala.
			{
			case ERoomDifficulty::NORMAL:
				NonRandEnemyClass = Spawner->EnemiesNormal;
				break;
			case ERoomDifficulty::HARD:
				NonRandEnemyClass = Spawner->EnemiesHard;
				break;
			default:
				checkNoEntry();
				break;
			}

			if (NonRandEnemyClass->IsValidLowLevelFast()) //Checando que a classe é não nula.
			{
				//Spawn do inimigo não randomicamente
				newEnemy = GetWorld()->SpawnActor<AEnemy>(NonRandEnemyClass, Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}

		if (newEnemy->IsValidLowLevelFast()) //Checando se o inimigo gerado é valido.
		{
			newEnemy->SpawnDefaultController(); //Spawn do controlador do inimigo
			Enemies.Add(newEnemy); //Adicionar o inimigo ao array de inimigos da sala.
			newEnemy->ParentRoom = this; //Sala pai do inimigo é a sala atual.
		}

		AEnemyController* controller = Cast<AEnemyController>(newEnemy->GetController());

		if (controller->IsValidLowLevelFast()) //Checando a validade do controlador e fazendo com que a sala pai do controlador seja a sala atual.
		{
			controller->ParentRoom = this;
		}
	}
}

TSubclassOf<AEnemy> ARoom::GetEnemyType(const TArray <TSubclassOf<AEnemy>>& EnemyClassArray,FRandomStream& Stream)
{
	TSubclassOf<AEnemy> enemyType = EnemyClassArray[Stream.FRandRange(0, EnemyClassArray.Num() - 1)]; //Usando um stream randomico para retornar o um inimigo dentro do array de inimigos de uma determinada dificuldade.

	return enemyType;

}

void ARoom::OnEnemiesDefeated()
{
	if (Enemies.Num() == 0 && bRoomHasEnemies) //Apenas checar se a sala tem inimigos
	{
		for (const auto& Porta : Doors) //Destrancar todas as portas da sala.
		{
			Porta->UnlockDoor();
		}
		
		//Desativando o delegate de overlap do trigger.
		bRoomHasEnemies = false;
		TriggerEnemiesActivate->OnComponentBeginOverlap.RemoveAll(this);
		TriggerEnemiesActivate->OnComponentEndOverlap.RemoveAll(this);
		UnlockDoors(); //Evento para o blueprint das portas

		AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
		ARoomGenerator* spawner = ARoomGenerator::GetRoomGenerator(GetWorld());

		if (player->IsValidLowLevelFast() && spawner->IsValidLowLevelFast()) //Salvar o jogador e as salas.
		{
			player->SavePlayerState();
			spawner->SaveRooms();
		}

	}

}

void ARoom::LockDoors()
{
	for (const auto& door : Doors) //Trancar todas as portas
	{
		door->LockDoor();
	}

}

void ARoom::ActivateEnemiesTriggerOnOverlap(class AActor* OtherActor)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && bRoomHasEnemies) //Checando que quem faz o overlap é do tipo do jogador e que a sala tem inimigos.
	{
		for (auto const& Enemy : Enemies) //Ativando o controlador de cada inimigo na sala.
		{
			AEnemyController* controller = Cast<AEnemyController>(Enemy->GetController());

			if (controller->IsValidLowLevelFast())
			{
				controller->ActivateEnemy();
			}
		}

		UpdateEnemiesHealth(player);
		LockDoors(); //Trancando as portas
	}
}

void ARoom::ActivateEnemiesTriggerEndOverlap(class AActor* OtherActor)
{
	if (Cast<AProtuXPlayer>(OtherActor) && bRoomHasEnemies) //Checando que quem faz o overlap é do tipo do jogador e que a sala tem inimigos.
	{
		for (auto const& Enemy : Enemies) //Desativando os controladores
		{
			AEnemyController* controller = Cast<AEnemyController>(Enemy->GetController());

			if (controller->IsValidLowLevelFast())
			{
				controller->DeactivateEnemy();
			}
		}
	}
}

void ARoom::ChangeRoomColor(FLinearColor newColor, USceneComponent* room)
{
	TArray<USceneComponent*> meshs;

	room->GetChildrenComponents(true, meshs); //Pegando as meshs que terão o seus materiais alterados.

	for (auto const& component : meshs)
	{
		UInstancedStaticMeshComponent* instMesh = Cast<UInstancedStaticMeshComponent>(component); 

		if (instMesh)
		{
			UMaterialInstanceDynamic* MID =  instMesh->CreateDynamicMaterialInstance(1); //Criando o material dinamico que tera a cor alterada.

			if (MID)
			{
				MID->SetVectorParameterValue("Base_Color", newColor); //Alterando a cor do material.
			}
		}
	}
}

