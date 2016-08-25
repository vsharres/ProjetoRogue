// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "EnergyPickUp.generated.h"

/**
* Class inherited from APickUp
* Class that represents a PickUp that increases player's energy
*/
UCLASS()
class PROTUX_API AEnergyPickUp : public APickUp
{
	GENERATED_BODY()

#pragma region Constructor

	/** Default Constructor */
	AEnergyPickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions
	
	/**
	* Delegate function to be executed when the collider begins an overlap with the player
	* Delegate signature determined by the OnBeginOverlap Delegate
	*/
	UFUNCTION()
		void ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	/**
	* Delegate function to be executed when the outline collider overlaps with the player
	* Delegate signature determined by the OnBeginOverlap Delegate
	*/
	UFUNCTION()
		void OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/**
	* Delegate function to be executed when the outline collider end an overlap with the player
	* Delegate signature determined by the OnEndOverlap Delegate
	*/
	UFUNCTION()
		void OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion Functions

};
