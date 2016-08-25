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
	//Inicializando as propriedades
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

	if (!IsAlive()) //checando se o inimigo está vivo, e se não estiver, remover o inimigo do array de inimigos da salapai
	{
		if (ParentRoom->IsValidLowLevelFast())
		{
			ParentRoom->RemoveEnemy(this);
		}

		OnEnemyDeath(); //disparar o evento para destruir o inimigo.
	}

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Criar objeto de save
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
	return GetMesh()->GetSocketLocation("Tiro_Bocal");
}

FRotator AEnemy::GetFiringDir()
{
	return GetMesh()->GetComponentRotation();
}

void AEnemy::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	Stats.Health -= damage;
	this->FlashDamage(); //evento para gerar o efeito de flash do mesh do inimigo
	AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player->IsValidLowLevelFast())
	{
		player->GenerateDamagePopUp(damage, this, projectile); //gerar o popup de dano para o jogador
	}

}

void AEnemy::ApplyProjectileStats(AProjectile* projectile)
{
	if (projectile->IsValidLowLevelFast()) //aplicar os stats do inimigo ao projetil
	{
		projectile->Stats = this->Stats;
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
	Stats.Damage += (currentLevel - 1) * 2.5f;
	Stats.Health += (currentLevel - 1) * 15.0f;
	Stats.MaxHealth += (currentLevel - 1) * 15.0f;

}

void AEnemy::SpawnPickUp()
{
	FRandomStream stream = FRandomStream();
	stream.GenerateNewSeed(); //criar novo seed de geração do pickup

	for (int32 index = 0; index < PickUpNumber; index++)
	{
		if (index == 0 && EnemyType == EEnemyType::BOSS) //se o inimigo for um boss, o primeiro pickup é sempre um item
		{
			AItemPickUp* pickItem = GetWorld()->SpawnActor<AItemPickUp>(ItemPickUpClass, GetActorLocation(), GetActorRotation());
			pickItem->ChooseItem(stream);

			continue;
		}

		if (stream.FRandRange(0, 100) >= HealthPickUpSpawnChance) //tentar fazer o spawn de um pickup de vida
		{

			AHealthPickUp* pickSpawn = GetWorld()->SpawnActor<AHealthPickUp>(HealthPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= EnergyPickUpSpawnChance) //tentar fazer o spawn de um pickup de energia
		{

			AEnergyPickUp* pickSpawn = GetWorld()->SpawnActor<AEnergyPickUp>(EnergyPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ScrapPickUpSpawnChance) //tentar fazer o spawn de um pickup de scrap
		{
			AScrapPickUP* pickSpawn = GetWorld()->SpawnActor<AScrapPickUP>(ScrapPickUpClass, GetActorLocation(), GetActorRotation());

			continue;
		}

	}

}


