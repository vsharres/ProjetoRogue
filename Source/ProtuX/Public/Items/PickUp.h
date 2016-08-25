// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "PickUp.generated.h"

/** Enum that represents the type of item. The type of the is associated with the effect caused on the player */
UENUM(BlueprintType)
enum class EPickUpType : uint8 {
	SCRAP,
	ENERGY,
	HEALTH,
	ITEM
};

/**
* Class inherited from AActor
* Abstract class which represents an object that the enemies drop as they are destroyed. PickUps can provide boost to health, energy, scrap or an item.
*/
UCLASS(abstract)
class PROTUX_API APickUp : public AActor
{
	GENERATED_BODY()
#pragma region Properties
	
protected:

	/** Collision component for the trigger to catch the PickUp */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		USphereComponent* TriggerCatch;

	/** Collision component for the trigger to show the outline of the PickUp */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		USphereComponent* TriggerOutline;

	/** PickUp mesh component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh;

public:

	/** Position delta vector from the center of the explosion force */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosionDelta;

	/** Explosion force magnitude */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosionForce;

	/** How much the PickUp increases health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		float IncHealth;

	/** How much the PickUp increases energy */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncEnergy;

	/** How much the PickUp increases scrap */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncScraps;

	/** PickUp type */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
		EPickUpType	Type;

#pragma endregion Properties

#pragma region Constructor

/** Default Constructor */
	APickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

	/**
	* Get function to return the collision component
	* @return Pointer to the collision component
	*/
	UFUNCTION(BlueprintPure, Category = "Colisor")
		USphereComponent* GetCollider();

	/**
	* Get function to return the PickUp Mesh component
	* @return Pointer to the mesh component
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		UStaticMeshComponent* GetMesh();

	/** BeginPlay event override */
	virtual void BeginPlay() override;

#pragma endregion Functions

	
	
};
