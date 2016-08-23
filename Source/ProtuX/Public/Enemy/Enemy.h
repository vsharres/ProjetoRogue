// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "DamageInterface.h"
#include "Enemy.generated.h"

/* Enemy type enum */
UENUM(BlueprintType)
enum class EEnemyType :uint8
{
	DRONE,
	TOWER,
	BOT,
	BOSS
};

/* Enemy attack type enum */
UENUM(BlueprintType)
enum class EAttackType :uint8
{
	MELEE,
	RANGE,
	AOE
};

/* Enemy stats struct */
USTRUCT()
struct FEnemyStats
{
	GENERATED_USTRUCT_BODY()

		/* Enemy Current health. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float Health;

	/* Enemy max health.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float MaxHealth;

	/* Enemy damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float Damage;

	/* Enemy rotation speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float RotationSpeed;

	/* Enemy fire rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float FireRate;

	/* Enemy accuracy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float Accuracy;

	/* Enemy muzzle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		float MuzzleSpeed;

	/* Enemy attack type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Struct")
		EAttackType AttackType;

	/* Standard constructor. */
	FEnemyStats(float heatlh = 100.0f,
		float damage = 1.0f,
		float rotSpeed = 1.0f,
		float fireRate = 1.0f,
		float accurary = 1.0f,
		float muzzleSpeed = 0.0f,
		EAttackType attackType = EAttackType::MELEE)
	{
		Health = heatlh;
		MaxHealth = heatlh;
		Damage = damage;
		RotationSpeed = rotSpeed;
		FireRate = fireRate;
		Accuracy = accurary;
		MuzzleSpeed = muzzleSpeed;
		AttackType = attackType;
	}

};

/* Class that represents an enemy in the game, which is controller by an AI */
UCLASS(ABSTRACT, Blueprintable)
class PROTUX_API AEnemy : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

#pragma region Properties
protected:

	/* Enemy Type. */
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		EEnemyType EnemyType;

	/* Number of pickups spawned by enemy on death. */
	UPROPERTY(EditAnywhere, Category = "PickUp")
		int32 PickUpNumber;

	/* Chance that a health pickup will be spawned. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float HealthPickUpSpawnChance;

	/* Chance that a energy pickup will be spawned. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float EnergyPickUpSpawnChance;

	/* Chance that a scrap pickup will be spawned.*/
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ScrapPickUpSpawnChance;

	/* Class of the energy pickup. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AEnergyPickUp> EnergyPickUpClass;

	/* Class of the health pickup. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AHealthPickUp> HealthPickUpClass;

	/* Class of the scrap pickup. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AScrapPickUP> ScrapPickUpClass;

	/*Class of the item pickup.*/
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AItemPickUp> ItemPickUpClass;


public:

	/* Enemy Stats. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FEnemyStats Stats;

	/* Pointer to the room in which the enemy is located. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
		TWeakObjectPtr<class ARoom> ParentRoom;

	/* Array with the last player positions, to be use in following the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		TArray<FVector> LastPlayerVelocity;

	/* Boolean that is true when the enemy is attacking. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool bIsAttacking;

	/* Boolean that is true when the enemy is dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool bIsDying;
#pragma endregion Properties

#pragma region Construtor
	/* Standard constructor. */
	AEnemy(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Functions

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called on begin play
	virtual void BeginPlay() override;

	/*
	* Get function for the enemy firing position.
	* @return FVector firing position.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		FVector GetFiringPos();

	/*
	* Get function for the enemy firing direction.
	* @return FRotator firing rotation.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		FRotator GetFiringDir();

	/*
	* Interface function to receive damage.
	* @param damage - float damage value.
	* @param projectile - pointer to the projectile that caused damage.
	* @param Hit - Hit struct.
	*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
		virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	/*
	* Function to check if the enemy is alive.
	* @return Boolean that is true if the enemy is alive.
	*/
	UFUNCTION()
		bool IsAlive();

	/*
		Function to calculate the enemy stats based on the current level.
		@param currentLevel - Integer value of the current level.
	*/
	UFUNCTION()
		virtual void CalculateStats(int32 currentLevel);

	/*
	* Function to spawn a pickup when the enemy dies.
	*/
	UFUNCTION(BlueprintCallable, Category = "PickUp")
		void SpawnPickUp();

	/*
	* Event to trigger a flash on the enemy material when it gets hit.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void FlashDamage();

	/*
	* Event triggered when the enemy dies.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void OnEnemyDeath();
	/*
	* Function to apply projectile stats to the base stats of the enemy.
	* @param projectile - Pointer to projectile to apply stats to.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		virtual void ApplyProjectileStats(AProjectile* projectile) override;

#pragma endregion Functions

};
