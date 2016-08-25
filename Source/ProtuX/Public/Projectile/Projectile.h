// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "Enemy.h"
#include "Projectile.generated.h"

/** Struct that represents the stats of a projectile. */
USTRUCT()
struct FProjectileStats
{
	GENERATED_USTRUCT_BODY()
public:

	/** Speed of the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Struct")
		float Speed;

	/** Damage caused by the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Struct")
		float Damage;

	/** Default Constructor. */
	FProjectileStats(float speed = 200.0f, float damage = 1.0f)
	{
		Speed = speed;
		Damage = damage;
	}

	/** Overload of the assignment operator to assign the player stats to the projectile. */
	FORCEINLINE FProjectileStats& operator=(const FPlayerStats& playerStats)
	{
		this->Speed = playerStats.MuzzleSpeed;
		this->Damage = playerStats.Damage;

		return *this;
	}

	/** Overload of the assignment operator to assign the enemy stats to the projectile. */
	FORCEINLINE FProjectileStats& operator=(const FEnemyStats& enemyStats)
	{
		this->Speed = enemyStats.MuzzleSpeed;
		this->Damage = enemyStats.Damage;

		return *this;
	}

};

/** Struct that holds the impact effects spawned by the projectile. */
USTRUCT()
struct FProjectileImpactEffect
{
	GENERATED_USTRUCT_BODY()
public:

	/** Particle system spawned on impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* Effect;

	/** SoundFX spawned on impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* ImpactSoundFX;

	/** Decal material spawned on impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UMaterial* DecalMaterial;

	/** Size of the decal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalSize;

	/** Life time of the decal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalHealth;

	/** Default Constructor. */
	FProjectileImpactEffect()
	{
		Effect = NULL;
		ImpactSoundFX = NULL;
		DecalMaterial = NULL;
		DecalSize = 2.0f;
		DecalHealth = 3.0f;
	}
};

/** Struct that holds the shooting effects spawned by the projectile.  */
USTRUCT()
struct FProjectileShootEffects
{
	GENERATED_USTRUCT_BODY()
public:

	/** Particle system spawned on shoot. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* ShootFlash;

	/** Sound FX spawned on shoot. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* ShootSound;

	/** Default Constructor. */
	FProjectileShootEffects()
	{
		ShootFlash = NULL;
		ShootSound = NULL;
	}
};

/**
*	Class inherited from AActor.
*	This class represents a projectile shoot by the player and enemies.
*	This is an abstract class, it will be used on particle blueprint for specific behaviors on types of particles (bouncing on walls, following enemies..)
*/
UCLASS(ABSTRACT, Blueprintable)
class PROTUX_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region Properties

public:

	/** Boolean indicating if the projectile is active. The projectile only moves, is visible and causes damage when he is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsActive;

	/** Projectile Stats. */
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		FProjectileStats Stats;

	/** Camera shake animation to be played when the projectile is shoot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UCameraShake> ShootCameraShake;

protected:

	/** Projectile movement component. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		UProjectileMovementComponent* MovementComp;

	/** Projectile collision component. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		USphereComponent* CollisionComp;

	/** Projectile Mesh component. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		UStaticMeshComponent* Mesh;

	/** Projectile impact effects struct. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FProjectileImpactEffect ImpactFX;

	/** Projectile shoot effects struct. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FProjectileShootEffects ShootFX;

#pragma endregion


#pragma region Constructor

public:
	/** Default Constructor. */
	AProjectile(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Functions

	/**
	* Get function for the projectile mesh component.
	* @return - Pointer to the mesh component.
	*/
	UFUNCTION(BlueprintPure, Category = "Component")
		UStaticMeshComponent* GetProjectileMesh();

	/**
	* Get function for the projectile movement component.
	* @return - Pointer to the movement component.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Comp", Keywords = "Get Mov Comp"), Category = "Projectile")
		UProjectileMovementComponent* GetMovComp();

	/**
	* Function to initialize the projectile.
	* @param initializer - Character pointer to the enemy or player that will be firing the projectile.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InitProj", Keywords = "Initialize Projectile"), Category = "Projectile")
		void InitializeProjectile(ACharacter* initializer);

	/**
	* Function to activate the projectile.
	* @param location - Location vector where the projectile will be initialized.
	* @param rotator - Rotation vector of the projectile to initialized.
	* @param initializer - Pointer to the Character that fired the projectile.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Activate Projectile", Keywords = "Activate Projectile"), Category = "Projectile")
		void ActivateProjectile(const FVector& location, const FRotator& rotator, ACharacter* initializer);

	/**
	* Function to deactivate a projectile.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Deactivate Projectile", Keywords = "Deactivate Projectile"), Category = "Projectile")
		void DeactivateProjectile();

	/**
	* Function to spawn impact effects on collision with surfaces.
	* @param Hit - Hit struct with data on the collision point.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Impact FX", Keywords = "Spawn Impacto Effects"), Category = "Projectile")
		void SpawnImpactFX(const FHitResult& Hit);

	/**
	* Function to spawn shooting effects.
	* @param location - Location where to spawn the particle effects.
	* @param rotator - Rotation of the particle effects.
	* @param component - Component to bind the effect to. (Cannon muzzle usually)
	* @param name -  Name of the bone mesh to bind the effect.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Shoot FX", Keywords = "Spawn Shoot Effects"), Category = "Projectile")
		void SpawnShootFX(const FVector& location, const FRotator& rotator, USceneComponent* component, FName name);

	/** Event called when the game begins, initialize variables. */
	virtual void BeginPlay() override;

	/** Called every frame. */
	virtual void Tick(float DeltaSeconds) override;

	/**
	* Event called when a particle hits a target.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Projectile")
		void OnHitTarget();

	/**
	* On hit delegate.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Hit", Keywords = "On Hit"), Category = "Projectile")
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion



};
