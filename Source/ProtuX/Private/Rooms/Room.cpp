// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Door.h"
#include "ProtuXPlayer.h"
#include "RoomGenerator.h"
#include "EnemySpawnerComponent.h"

ARoom::ARoom(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing trigger to activate enemies
	TriggerEnemiesActivate = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerAtivarInimigos"));
	TriggerEnemiesActivate->SetBoxExtent(FVector(300.0f, 300.0f, 32.0f));
	
	RootComponent = TriggerEnemiesActivate;
	
	//initializing properties
	bCanBeDamaged = false;
	NumberDoors = ENumberDoors::ONE;
	RoomDirection = ERoomShape::Default;
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
	Super::Tick(DeltaTime); 

	OnEnemiesDefeated();//check if enemies where defeated

}

FVector ARoom::GetRoomScale() const
{
	return RoomScale;
}

float ARoom::GetRoomOffset() const
{
	return RoomOffset;
}

ENumberDoors ARoom::GetNumDoors() const
{
	return NumberDoors;
}

ERoomShape ARoom::GetRoomShape() const
{
	return RoomDirection;
}

ERoomType ARoom::GetRoomType() const
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
	//unbind delegate functions
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
	if (!bRoomHasEnemies)//if the room has no enemies, skip spawn
		return;

	TInlineComponentArray<UEnemySpawnerComponent*> Components; 
	this->GetComponents(Components); //Find all spawner components in the room

	TArray<TSubclassOf<AEnemy>> EnemyType;

	switch (Difficulty) //chose enemy based on the room's difficulty
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

	for (const auto& Spawner : Components) //for each spawner, spawn an enemy
	{
		AEnemy* newEnemy =  NULL;

		if (Spawner->bSpawnRandomly) 
		{
			//check that only valid classes are used
			if (Spawner->GetNumEnemies(Difficulty) > 0)
			{
				//randomly spawn enemy
				newEnemy = GetWorld()->SpawnActor<AEnemy>(Spawner->SelectEnemyRand(Stream,Difficulty), Spawner->GetComponentLocation(), FRotator::ZeroRotator); 
			}
			else 
			{
				newEnemy = GetWorld()->SpawnActor<AEnemy>(GetEnemyType(EnemyType,Stream), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}
		else
		{
			TSubclassOf<AEnemy> NonRandEnemyClass;
			

			switch (Difficulty) //chose enemy based on the room's difficulty
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

			if (NonRandEnemyClass->IsValidLowLevelFast())
			{
				//Spawn enemy non randomly
				newEnemy = GetWorld()->SpawnActor<AEnemy>(NonRandEnemyClass, Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}

		if (newEnemy->IsValidLowLevelFast())
		{
			newEnemy->SpawnDefaultController(); //spawn the enemy controller
			Enemies.Add(newEnemy); 
			newEnemy->ParentRoom = this;
		}

		AEnemyController* controller = Cast<AEnemyController>(newEnemy->GetController());

		if (controller->IsValidLowLevelFast())
		{
			controller->ParentRoom = this;
		}
	}
}

TSubclassOf<AEnemy> ARoom::GetEnemyType(const TArray <TSubclassOf<AEnemy>>& EnemyClassArray,FRandomStream& Stream)
{
	//Using a randmly stream to choose an enemy of a given difficulty
	TSubclassOf<AEnemy> enemyType = EnemyClassArray[Stream.FRandRange(0, EnemyClassArray.Num() - 1)]; 

	return enemyType;

}

void ARoom::OnEnemiesDefeated()
{
	if (Enemies.Num() == 0 && bRoomHasEnemies)
	{
		for (const auto& Porta : Doors) //Unlock all doors in the room
		{
			Porta->UnlockDoor();
		}
		
		//deactivating the overlap trigger delegate
		bRoomHasEnemies = false;
		TriggerEnemiesActivate->OnComponentBeginOverlap.RemoveAll(this);
		TriggerEnemiesActivate->OnComponentEndOverlap.RemoveAll(this);
		UnlockDoors(); //Blueprint event

		AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
		ARoomGenerator* spawner = ARoomGenerator::GetRoomGenerator(GetWorld());

		if (player->IsValidLowLevelFast() && spawner->IsValidLowLevelFast()) //Save player and rooms
		{
			player->SavePlayerState();
			spawner->SaveRooms();
		}

	}

}

void ARoom::LockDoors()
{
	for (const auto& door : Doors) //Lock all doors in the room
	{
		door->LockDoor();
	}

}

void ARoom::ActivateEnemiesTriggerOnOverlap(class AActor* OtherActor)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && bRoomHasEnemies) //Checking that is a player that is overlapping with the trigger and that the room has enemies
	{
		for (auto const& Enemy : Enemies) //activate each enemy controller
		{
			AEnemyController* controller = Cast<AEnemyController>(Enemy->GetController());

			if (controller->IsValidLowLevelFast())
			{
				controller->ActivateEnemy();
			}
		}

		UpdateEnemiesHealth(player);
		LockDoors();
	}
}

void ARoom::ActivateEnemiesTriggerEndOverlap(class AActor* OtherActor)
{
	if (Cast<AProtuXPlayer>(OtherActor) && bRoomHasEnemies) //Checking that is a player that is overlapping with the trigger and that the room has enemies
	{
		for (auto const& Enemy : Enemies) //Deactivating each enemy controller
		{
			AEnemyController* controller = Cast<AEnemyController>(Enemy->GetController());

			if (controller->IsValidLowLevelFast())
			{
				controller->DeactivateEnemy();
			}
		}
	}
}

void ARoom::ChangeRoomColor(FLinearColor newColor, USceneComponent* roomLights)
{
	TArray<USceneComponent*> meshs;

	roomLights->GetChildrenComponents(true, meshs); //Get all meshes that will change

	for (auto const& component : meshs)
	{
		UInstancedStaticMeshComponent* instMesh = Cast<UInstancedStaticMeshComponent>(component); 

		if (instMesh)
		{
			
			UMaterialInstanceDynamic* MID =  instMesh->CreateDynamicMaterialInstance(1); 

			if (MID)
			{
				MID->SetVectorParameterValue("Base_Color", newColor);
			}
		}
	}
}

