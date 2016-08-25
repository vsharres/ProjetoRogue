// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProtuXPlayer.h"
#include "Projectile.h"
#include "PassiveItem.h"
#include "ProjectileItem.h"

AProtuXPlayer::AProtuXPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Inicializando propriedades
	PrimaryActorTick.bCanEverTick = true;

	Stats = FPlayerStats();
	bHasKey = false;
	PassiveItems.Empty();
	CooldDownRate = 1.0f;
	CooldownTime = 2.0f;
	Coins = 0;
	CurCooldown = CooldownTime;
	bFoundItem = false;

	NumProjectiles = 20;

	Name = "Mark I";

}

void AProtuXPlayer::InitializePlayer()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex) == false ? UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex) : NULL;

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->bIsNewGame && !SaveInst->bIsContinuingGame || gameMode->bNoSave) //caso nao seja um novo novo, carregar o jogador
	{
		NewPlayer();
	}
	else
	{
		LoadPlayerState();
	}

	InitializeProjectile(false); //inicializar o projetil.
}

void AProtuXPlayer::GenerateName(int32 index)
{
	FString num;

	int32 temp = index;

	while (temp != 0 && temp <= 999) //gerar o nome da versão do prototipo em numeral romanos
	{
		if (temp >= 100)
		{
			switch (temp / 100)
			{
			case 1:
				num += "C";
				break;
			case 2:
				num += "CC";
				break;
			case 3:
				num += "CCC";
				break;
			case 4:
				num += "CD";
				break;
			case 5:
				num += "D";
				break;
			case 6:
				num += "DC";
				break;
			case 7:
				num += "DCC";
				break;
			case 8:
				num += "DCCC";
				break;
			case 9:
				num += "MC";
				break;
			default:
				break;
			}

			temp -= (temp / 100) * 100;
		}
		else if (temp >= 10)
		{

			switch (temp / 10)
			{
			case 1:
				num += "X";
				break;
			case 2:
				num += "XX";
				break;
			case 3:
				num += "XXX";
				break;
			case 4:
				num += "XL";
				break;
			case 5:
				num += "L";
				break;
			case 6:
				num += "LX";
				break;
			case 7:
				num += "LXX";
				break;
			case 8:
				num += "LXXX";
				break;
			case 9:
				num += "XC";
				break;
			default:
				break;
			}

			temp -= (temp / 10) * 10;
		}
		else if (temp < 10)
		{
			switch (temp)
			{
			case 1:
				num += "I";
				break;
			case 2:
				num += "II";
				break;
			case 3:
				num += "III";
				break;
			case 4:
				num += "IV";
				break;
			case 5:
				num += "V";
				break;
			case 6:
				num += "VI";
				break;
			case 7:
				num += "VII";
				break;
			case 8:
				num += "VIII";
				break;
			case 9:
				num += "IX";
				break;
			default:
				break;
			}

			temp = 0;

		}

	}

	if (num != "")
	{
		Name = "Mark " + num;
	}
	else
	{
		Name = "Mark M";
	}

}

void AProtuXPlayer::UpdateProjectileStats()
{
	GetCharacterMovement()->MaxWalkSpeed = Stats.Speed; //atualizar a velocidade de movimentação do personagem do jogador com os stats
}

bool AProtuXPlayer::IsAlive()
{
	if (Stats.Health > 0.01) //checar vida
	{
		return true;
	}

	return false;
}

void AProtuXPlayer::AddHealth(float health)
{
	this->Stats.AddHealth(health);

}

void AProtuXPlayer::AddEnergy(float energy)
{
	Stats.AddEnergy(energy);
}

void AProtuXPlayer::AddCoins(int32 value)
{
	Coins += value; 

	if (Coins < 0) 
	{
		Coins = 0;
	}
}

void AProtuXPlayer::SavePlayerState()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNoSave)
		return;

	//Criando objeto de save
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//salvar as propriedades do jogador
		SaveInst->bIsNewGame = false;
		SaveInst->Stats.SetStats(this->Stats);
		SaveInst->Scrap = this->Coins;
		SaveInst->bHasKey = this->bHasKey;

		//Salvando transform do jogador
		SaveInst->PlayerLocation = this->GetActorLocation();
		SaveInst->PlayerRotation = this->GetActorRotation();

		if (FoundProjectile) //salvar referência ao asset do projetil encontrado
		{
			SaveInst->FoundProjectileRef = FStringAssetReference(this->FoundProjectile).ToString();
		}

		SaveInst->bHasFoundItem = this->bFoundItem;

		SaveInst->PassiveItemsRef.Empty();
		for (const auto& item : PassiveItems) //salvar as referências aos assets dos itens passivos.
		{

			SaveInst->PassiveItemsRef.Add(FStringAssetReference(item->GetClass()).ToString());
		}

		//Salvar jogador.
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXPlayer::LoadPlayerState()
{
	//Criar objeto de save
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//Carregando propriedades
		GenerateName(SaveInst->NumGames);
		this->Stats.SetStats(SaveInst->Stats);
		this->Coins = SaveInst->Scrap;
		
		if (SaveInst->bIsContinuingGame)
		{
			//Carregando transform do jogador
			this->SetActorLocation(SaveInst->PlayerLocation);
			this->SetActorRotation(SaveInst->PlayerRotation);
			this->bHasKey = SaveInst->bHasKey;
		}

		if (!SaveInst->FoundProjectileRef.IsEmpty()) //criando o projetil encontrando
		{
			UProjectileItem* projectileItem = NewObject<UProjectileItem>(this, StaticLoadClass(UProjectileItem::StaticClass(), NULL, *SaveInst->FoundProjectileRef));

			if (projectileItem)
			{
				this->FoundProjectile = projectileItem->GetClass();
			}
		}


		if (SaveInst->PassiveItemsRef.Num() > 0) //criando os itens passivos encontrados
		{
			this->PassiveItems.Empty();
			for (const auto& passivo : SaveInst->PassiveItemsRef)
			{
				UPassiveItem* passiveItem = NewObject<UPassiveItem>(this, StaticLoadClass(UPassiveItem::StaticClass(), NULL, *passivo));

				if (passiveItem)
				{
					passiveItem->InitializeItem(this);
				}
			}
		}

	}

}

void AProtuXPlayer::NewPlayer()
{
	//Criando um novo jogador
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		GenerateName(SaveInst->NumGames); //isar o número de jogos para determinar o número da versão do prototipo
	}

}

void AProtuXPlayer::UseItem(bool bIsDeactivated/**= false*/)
{
	if (FoundProjectile->IsValidLowLevelFast()) //checar que o projetil encontrado é valido
	{
		InitializeProjectile(bIsDeactivated); //inicializar o projetil e atulizar o mesh do canhão
		UpdateMesh();
	}
}

void AProtuXPlayer::InitializeProjectile(bool bIsDeactivated/**= false*/)
{
	if (CurrentProjectile ==  NULL && !bIsDeactivated) //checar que o projetil atual é valido e não esta sendo desativado
	{
		//Inicializar o projetil atual como o projetil inicial do jogo.
		CurrentProjectile = NewObject<UProjectileItem>(this, StartingProjectile);
		CurrentProjectile->InitializeItem(this);
		GenerateProjectilePool();

	}
	else if (bIsDeactivated)
	{
		//Desativar o item ativo e reverter o projetil ao projetil inicial do jogo.
		CurrentProjectile->DeactivateItem();
		CurrentProjectile->RemoveItem();
		CurrentProjectile = NewObject<UProjectileItem>(this, StartingProjectile);
		CurrentProjectile->InitializeItem(this);
		GenerateProjectilePool();
	}
	else
	{
		//Ativar o item ativo e setar o projetil atual como o projetil do item ativo.
		CurrentProjectile->DeactivateItem();
		CurrentProjectile->RemoveItem();
		CurrentProjectile = NewObject<UProjectileItem>(this, FoundProjectile);
		CurrentProjectile->InitializeItem(this);
		GenerateProjectilePool();

		CurrentProjectile->ActivateItem();
	}

}

void AProtuXPlayer::GenerateProjectilePool()
{
	if (ProjectilePool.Num() > 0) //Deletar os projeteis que já estão no array.
	{
		ProjectilePool.Empty();
	}

	for (int32 index = 0; index < NumProjectiles; index++) //criar os projeteis do pool
	{
		FVector firePos = FVector(0, 0, 1000);

		//Spawn do projétil
		AProjectile* shoot = GetWorld()->SpawnActor<AProjectile>(CurrentProjectile->Projectile, firePos, GetControlRotation());

		if (shoot->IsValidLowLevelFast())
		{
			shoot->Instigator = this; //Player é o responsável pelo dano do jogador.
			shoot->SetActorHiddenInGame(true); //Esconder o projetil
			shoot->Instigator = this;
			ProjectilePool.Add(shoot); //Adicionar ao pool
		}
	}

	//pegar a cor do projetil atual e salvar na variável projetilCor
	UMaterialInstanceDynamic* MID;
	MID = ProjectilePool[0]->GetProjectileMesh()->CreateDynamicMaterialInstance(0, ProjectilePool[0]->GetProjectileMesh()->GetMaterial(0));

	if (MID)
	{
		MID->GetVectorParameterValue("Base_Cor", ProjectileColor);
	}

}

// Called every frame
void AProtuXPlayer::Tick(float DeltaTime)
{
	//ItemCooldown(DeltaTime);

	Super::Tick(DeltaTime);
}

void AProtuXPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ProjectilePool.Empty(); 
	PassiveItems.Empty();

	Super::EndPlay(EndPlayReason);
}

void AProtuXPlayer::ItemCooldown(float DeltaTime)
{
	if (CurrentProjectile->bIsActive)
	{
		Stats.Energy -= CurrentProjectile->EnergyRequired * DeltaTime;

		if (Stats.Energy <= 0.0f)
		{
			Stats.Energy = 0.0f;
			UseItem(true);
		}

	}

}

void AProtuXPlayer::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	this->Stats.Health -= damage; //receber o dano
	GenerateDamageCircleUI(Hit); //gerar o círculo de dano.

	if (Stats.Health <= 0) //se a vida for menor do que 0, o jogador morreu
	{
		OnPlayerDeath();
	}
}

void AProtuXPlayer::ApplyProjectileStats(AProjectile* projectile)
{
	if (projectile->IsValidLowLevelFast())
	{
		projectile->Stats = this->Stats; //aplicar os stats do jogador ao projétil.
	}
}

