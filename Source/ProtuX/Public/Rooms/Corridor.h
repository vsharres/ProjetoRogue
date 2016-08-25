// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Corridor.generated.h"

/**
*	Class inherited from AActor.
*	It represents a corridor between rooms, a corridor also has a shop for buying items.
*/
UCLASS()
class PROTUX_API ACorridor : public AActor
{
	GENERATED_BODY()

#pragma region Properties

private:

	/** Position offset, used to calculate the final transform of the corridor. */
	UPROPERTY(EditDefaultsOnly)
		float OffsetCorridor;

	/** Default scale of the corridor. */
	UPROPERTY(EditDefaultsOnly)
		FVector StandardScale;

#pragma endregion

#pragma region Constructor

public:
	/** Default Constructor. */
	ACorridor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Functions

	/**
	* Get function of the corridor scale.
	* @return FVector scale value.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		FVector GetScale();

	/**
	* Get function of the position offset.
	* @return float offset value.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		float GetOffset();

#pragma endregion
	
	
};
