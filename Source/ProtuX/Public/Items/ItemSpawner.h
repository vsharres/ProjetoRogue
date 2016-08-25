// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/**
* Class inherited from AActor.
* Class responsible for spawning an item on the item room on a level.
*/
UCLASS()
class PROTUX_API AItemSpawner : public AActor
{
	GENERATED_BODY()

#pragma region Properties
protected:

	/** Pointer to the spawned item */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
	class UItem* SpawnedItem;

	/** Class of the item to be spawned */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		TSubclassOf<UItem> ItemClass;

	/** Class array with all possible items */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		TArray<TSubclassOf<UItem>> PossibleItems;

	/** Item spawner collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
		UCapsuleComponent* Collider;

public:

	/** Random generation seed. This is the same seed utilized by the room generator */
	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;

#pragma endregion Properties
	
#pragma region Constructor

	/** Default Constructor */
	AItemSpawner(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

};
