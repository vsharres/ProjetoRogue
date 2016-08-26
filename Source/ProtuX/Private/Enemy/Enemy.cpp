// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Enemy.h"
#include "Room.h"
#include "Projectile.h"
#include "EnergyPickUp.h"
#include "ScrapPickUP.h"
#include "HealthPickUp.h"
#include "ItemPickUp.h"

AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing the base properties
	PrimaryActorTick.bCanEverTick = true;

	EnemyType = EEnemyType::DRONE;
	Stats = FEnemyStats();
	PickUpNumber = 1;
	HealthPickUpSpawnChance = 90.0f;
	EnergyPickUpSpawnChance = 75.0f;
	ScrapPickUpSpawnChance = 25.0f;

	bIsAttacking = false;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Checking if the enemy is still alive, and if it is not, remove the enemy from the array of enemies in the room
	if (!IsAlive()) 
	{
		if (ParentRoom->IsValidLowLevelFast())
		{
			ParentRoom->RemoveEnemy(this);
		}

		OnEnemyDeath(); //trigger the event to destroy the enemy
	}

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//loading the level to calculate the enemy stats
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	int32 level = 1;
	if (SaveInst)
	{
		level = SaveInst->CurrentLevel;
	}

	CalculateStats(level);

}

FVector AEnemy::GetFiringPos()
{
	return GetMesh()->GetSocketLocation("Tiro_Bocal"); //the firing position is the a socket in the mesh
}

FRotator AEnemy::GetFiringDir()
{
	return GetMesh()->GetComponentRotation();
}

void AEnemy::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	Stats.Health -= damage;
	this->FlashDamage(); //trigger the flashing effect on the enemy's mesh material
	AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player->IsValidLowLevelFast())
	{
		player->GenerateDamagePopUp(damage, this, projectile); //spawn the damage pop up on the player HUD
	}

}

void AEnemy::ApplyProjectileStats(AProjectile* projectile)
{
	if (projectile->IsValidLowLevelFast()) 
	{
		projectile->Stats = this->Stats; //Applying the the projectile stats on the enemy
	}
}

bool AEnemy::IsAlive()
{
	if (Stats.Health > 0)
	{
		return true;
	}

	return false;
}

void AEnemy::CalculateStats(int32 currentLevel)
{
	//calculating the stats per level
	Stats.Damage += (currentLevel - 1) * 2.5f;
	Stats.Health += (currentLevel - 1) * 15.0f;
	Stats.MaxHealth += (currentLevel - 1) * 15.0f;

}

void AEnemy::SpawnPickUp()
{
	FRandomStream stream = FRandomStream();
	stream.GenerateNewSeed(); //generate a new random stream for generating pickups

	//spawning each pickup
	for (int32 index = 0; index < PickUpNumber; index++)
	{
		if (index == 0 && EnemyType == EEnemyType::BOSS) //If the defeated enemy is a boss, the first pickuip is always an item
		{
			AItemPickUp* pickItem = GetWorld()->SpawnActor<AItemPickUp>(ItemPickUpClass, GetActorLocation(), GetActorRotation());
			pickItem->ChooseItem(stream);

			continue;
		}

		if (stream.FRandRange(0, 100) >= HealthPickUpSpawnChance) //trying to spawn a health pickup
		{

			AHealthPickUp* pickSpawn = GetWorld()->SpawnActor<AHealthPickUp>(HealthPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= EnergyPickUpSpawnChance) //trying to spawn an energy pickup
		{

			AEnergyPickUp* pickSpawn = GetWorld()->SpawnActor<AEnergyPickUp>(EnergyPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ScrapPickUpSpawnChance) //trying to spawn a scrap pickup
		{
			AScrapPickUP* pickSpawn = GetWorld()->SpawnActor<AScrapPickUP>(ScrapPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

	}

}


