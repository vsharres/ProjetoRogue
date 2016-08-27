// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProtuXPlayer.h"
#include "Projectile.h"
#include "PassiveItem.h"
#include "ProjectileItem.h"

AProtuXPlayer::AProtuXPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Initializing properties
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

	//Instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//check if save game exist, if not create one
	UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex) == false ? UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex) : NULL;

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->bIsNewGame && !SaveInst->bIsContinuingGame || gameMode->bNoSave) //checking if it is a new game, if not, load player state
	{
		NewPlayer();
	}
	else
	{
		LoadPlayerState();
	}

	InitializeProjectile(false); //initialize projectile.
}

void AProtuXPlayer::GenerateName(int32 index)
{
	FString num;

	int32 temp = index;

	while (temp != 0 && temp <= 999) //generate the version of the robot using roman numerals
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
	//Update the player movement speed with its current stats
	GetCharacterMovement()->MaxWalkSpeed = Stats.Speed;
}

bool AProtuXPlayer::IsAlive()
{
	if (Stats.Health > 0.01)
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

	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//load save game slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//save player's properties
		SaveInst->bIsNewGame = false;
		SaveInst->Stats.SetStats(this->Stats);
		SaveInst->Scrap = this->Coins;
		SaveInst->bHasKey = this->bHasKey;
		SaveInst->PlayerLocation = this->GetActorLocation();
		SaveInst->PlayerRotation = this->GetActorRotation();

		//save asset reference of the found projectile item
		if (FoundProjectile)
		{
			SaveInst->FoundProjectileRef = FStringAssetReference(this->FoundProjectile).ToString();
		}

		SaveInst->bHasFoundItem = this->bFoundItem;

		SaveInst->PassiveItemsRef.Empty();
		for (const auto& item : PassiveItems) //save asset references for the passive item the player currently has
		{

			SaveInst->PassiveItemsRef.Add(FStringAssetReference(item->GetClass()).ToString());
		}

		//save to slot
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXPlayer::LoadPlayerState()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	//Load slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//loading properties and generating name
		GenerateName(SaveInst->NumGames);
		this->Stats.SetStats(SaveInst->Stats);
		this->Coins = SaveInst->Scrap;
		
		if (SaveInst->bIsContinuingGame)
		{
			//loading transform information
			this->SetActorLocation(SaveInst->PlayerLocation);
			this->SetActorRotation(SaveInst->PlayerRotation);
			this->bHasKey = SaveInst->bHasKey;
		}

		if (!SaveInst->FoundProjectileRef.IsEmpty()) //spawning the found item
		{
			//using the ref to find the blueprint asset that generated the item
			UProjectileItem* projectileItem = NewObject<UProjectileItem>(this, StaticLoadClass(UProjectileItem::StaticClass(), NULL, *SaveInst->FoundProjectileRef));

			if (projectileItem)
			{
				this->FoundProjectile = projectileItem->GetClass();
			}
		}


		if (SaveInst->PassiveItemsRef.Num() > 0)  //generating the passive item
		{
			this->PassiveItems.Empty();
			for (const auto& passive : SaveInst->PassiveItemsRef)
			{
				UPassiveItem* passiveItem = NewObject<UPassiveItem>(this, StaticLoadClass(UPassiveItem::StaticClass(), NULL, *passive));

				if (passiveItem)
				{
					//initialize passive item
					passiveItem->InitializeItem(this);
				}
			}
		}

	}

}

void AProtuXPlayer::NewPlayer()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	//Load slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		GenerateName(SaveInst->NumGames); //generating new name
	}

}

void AProtuXPlayer::UseItem(bool bIsDeactivated/**= false*/)
{
	if (FoundProjectile->IsValidLowLevelFast())
	{
		InitializeProjectile(bIsDeactivated); //initialize projectile and update cannon mesh
		UpdateMesh();
	}
}

void AProtuXPlayer::InitializeProjectile(bool bIsDeactivated/**= false*/)
{
	if (CurrentProjectile ==  NULL && !bIsDeactivated) //checking that the current projectile does not exist and is active
	{
		//initialize the currenc projectile as the starting projectile
		CurrentProjectile = NewObject<UProjectileItem>(this, StartingProjectile);
		CurrentProjectile->InitializeItem(this);
		GenerateProjectilePool();

	}
	else if (bIsDeactivated)
	{
		//deactivate the projectile item and revert to the starting projectile
		CurrentProjectile->DeactivateItem();
		CurrentProjectile->RemoveItem();
		CurrentProjectile = NewObject<UProjectileItem>(this, StartingProjectile);
		CurrentProjectile->InitializeItem(this);
		GenerateProjectilePool();
	}
	else
	{
		//activate the projectile item and set the current projectile as the found projectile
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
	if (ProjectilePool.Num() > 0) //save checking and delete all projectile currently in the projectile pool
	{
		ProjectilePool.Empty();
	}

	for (int32 index = 0; index < NumProjectiles; index++) //generate each projectile in the projectile pool
	{
		FVector firePos = FVector(0, 0, 1000);

		//Spawn projectile
		AProjectile* shoot = GetWorld()->SpawnActor<AProjectile>(CurrentProjectile->Projectile, firePos, GetControlRotation());

		if (shoot->IsValidLowLevelFast())
		{
			shoot->Instigator = this; //setting the player as the instigator
			shoot->SetActorHiddenInGame(true); 
			ProjectilePool.Add(shoot); //add projectile to the pool
		}
	}

	//pegar a cor do projetil atual e salvar na variável projetilCor
	//get the current projectile color and save it in ts variable
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
	//empty arrays
	ProjectilePool.Empty(); 
	PassiveItems.Empty();

	Super::EndPlay(EndPlayReason);
}

void AProtuXPlayer::ItemCooldown(float DeltaTime)
{
	if (CurrentProjectile->bIsActive) //check if the item is active
	{
		Stats.Energy -= CurrentProjectile->EnergyRequired * DeltaTime; //update energy

		//if energy is bigger than 0, use the item
		if (Stats.Energy <= 0.0f)
		{
			Stats.Energy = 0.0f;
			UseItem(true);
		}

	}

}

void AProtuXPlayer::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	this->Stats.Health -= damage;
	GenerateDamageCircleUI(Hit);

	if (Stats.Health <= 0) 
	{
		OnPlayerDeath();
	}
}

void AProtuXPlayer::ApplyProjectileStats(AProjectile* projectile)
{
	if (projectile->IsValidLowLevelFast())
	{
		projectile->Stats = this->Stats;
	}
}

