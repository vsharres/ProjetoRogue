// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "RangedEnemy.h"
#include "Projectile.h"

ARangedEnemy::ARangedEnemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	Stats.AttackType = EAttackType::RANGE;
	EnemyType = EEnemyType::TOWER;
	NumProjectiles = 10;
}

void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	GenerateProjectilesPool(); //generating projectile pool
}

void ARangedEnemy::Destroyed()
{
	ProjectilePool.Empty(); //emptying the projectile pool

	Super::Destroyed();
}

void ARangedEnemy::CalculateStats(int32 currentLevel)
{
	Super::CalculateStats(currentLevel);

	//calculating stats for a ranged enemy
	Stats.FireRate += (currentLevel - 1)* 1.0f;
	Stats.Accuracy += (currentLevel - 1) * 0.5f;
	Stats.MuzzleSpeed += (currentLevel - 1) * 400.0f;
}

void ARangedEnemy::GenerateProjectilesPool()
{
	if (ProjectilePool.Num() > 0) //sanity check to empty the projectile pool
	{
		ProjectilePool.Empty();
	}

	for (int32 index = 0; index < NumProjectiles; index++) //generating a new pool of projectiles
	{
		FVector firingPos = FVector(GetActorLocation().X, GetActorLocation().Y, 1000); //hiding the projectiles at a height of 1000

		AProjectile* shoot = GetWorld()->SpawnActor<AProjectile>(Projectile, firingPos, GetControlRotation()); //spawning the projectile

		if (shoot->IsValidLowLevelFast())
		{
			shoot->Instigator = this; //setting this enemy as the instigator when this projectile causes damage to the player
			shoot->SetActorHiddenInGame(true); //hide the projectile
			ProjectilePool.Add(shoot); //adding the projectile to the pool
		}
	}
}

void ARangedEnemy::Attack_Implementation() //Implementation in the case where blueprints don't override the basic implementation 
{
	for (auto const& proj : ProjectilePool) 
	{
		if (!proj->bIsActive) //check if the projectile is not active
		{
			//Setting the firing position and direction, giving a random deviation for the aim
			FVector posShoot = GetFiringPos();
			FRotator shootDirection = GetFiringDir();
			FVector direction = FMath::VRandCone(shootDirection.Vector(), FMath::DegreesToRadians(Stats.Accuracy / 2.0f));

			//Activate the projectile and spawning the effects
			proj->ActivateProjectile(posShoot, direction.Rotation(), this);
			proj->SpawnShootFX(posShoot, shootDirection, GetMesh(), TEXT("Tiro_Bocal"));
			break;
		}
	}

}

