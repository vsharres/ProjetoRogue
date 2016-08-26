// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "RangedEnemy.generated.h"

/**
* Class inherited from AEnemy.
* Class that represents a type of enemy that can shoot projectiles. 
*/
UCLASS()
class PROTUX_API ARangedEnemy : public AEnemy
{
	GENERATED_BODY()

#pragma region Properties
public:
		/** Class of the projectile that will be fired */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<class AProjectile> Projectile;

		/** Projectiles pool */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
			TArray<AProjectile*> ProjectilePool;

		/** Number of projectiles in the pool */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
			int32 NumProjectiles;

		/** Boolean value of true when the enemy is firing */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
			bool bIsFiring;

#pragma endregion Properties

#pragma region Construtor

		/** Default Constructor */
		ARangedEnemy(const FObjectInitializer& ObjectInitializer);

#pragma endregion Construtor

#pragma region Functions

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Destroyed() override;

		/**
		* Override of the calculate stats, so that the enemy stats are calculates for a given level
		* @param currentLevel - Current game level
		*/
		virtual void CalculateStats(int32 currentLevel) override;

		/** Function to generate the projectile pool */
		UFUNCTION()
			void GenerateProjectilesPool();

		/** Function to fire an projectile. */
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Attack", Keywords = "Attack"), Category = "Enemy")
			void Attack();
		virtual void Attack_Implementation();

#pragma endregion Functions

		
	
	
};
