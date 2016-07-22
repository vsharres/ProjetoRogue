// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "RangedEnemy.h"
#include "Projectile.h"

ARangedEnemy::ARangedEnemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	Stats.AttackType = EAttackType::RANGE;
	EnemyType = EEnemyType::TOWER;
	NumProjectiles = 10;
}

void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	GenerateProjectilesPool(); //gerar o pool de projeteis
}

void ARangedEnemy::Destroyed()
{
	ProjectilePool.Empty(); //esvaziar o pool de projeteis

	Super::Destroyed();
}

void ARangedEnemy::CalculateStats(int32 currentLevel)
{
	Super::CalculateStats(currentLevel);

	Stats.FireRate += (currentLevel - 1)* 1.0f;
	Stats.Accuracy += (currentLevel - 1) * 0.5f;
	Stats.MuzzleSpeed += (currentLevel - 1) * 400.0f;
}

void ARangedEnemy::GenerateProjectilesPool()
{
	if (ProjectilePool.Num() > 0) //se o pool j� possui proj�teis, esvaziar o pool
	{
		ProjectilePool.Empty();
	}

	for (int32 index = 0; index < NumProjectiles; index++) //criar um novo pool de proj�teis
	{
		FVector firingPos = FVector(GetActorLocation().X, GetActorLocation().Y, 1000);

		AProjectile* shoot = GetWorld()->SpawnActor<AProjectile>(Projectile, firingPos, GetControlRotation());

		if (shoot->IsValidLowLevelFast())
		{
			shoot->Instigator = this; //setar esse inimigo como o respons�vel pelo dano causado pelo projetil.
			shoot->SetActorHiddenInGame(true); //esconder o proj�til
			shoot->Instigator = this;
			ProjectilePool.Add(shoot);
		}
	}
}

void ARangedEnemy::Attack_Implementation()
{
	for (auto const& proj : ProjectilePool) //checar o primeiro proj�til nao ativo dentro do pool de proj�teis
	{
		if (!proj->bIsActive)
		{
			//Determinar a posicao da onde o tiro sai, com a rota��o apontada para o jogador com um desvio rand�mico.
			FVector posShoot = GetFiringPos();
			FRotator shootDirection = GetFiringDir();
			FVector direction = FMath::VRandCone(shootDirection.Vector(), FMath::DegreesToRadians(Stats.Accuracy / 2.0f));

			//Ativar o proj�til atirado e gerar os efeitos de tiro.
			proj->ActivateProjectile(posShoot, direction.Rotation(), this);
			proj->SpawnShootFX(posShoot, shootDirection, GetMesh(), TEXT("Tiro_Bocal"));
			break;
		}
	}

}

