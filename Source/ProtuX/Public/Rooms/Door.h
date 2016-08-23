// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

/*
* Enum with the door direction
*/
UENUM(BlueprintType)
enum class EDoorDirection : uint8
{
	WEST,
	NORTH,
	EAST,
	SOUTH,

};


/* 
* Class inherited from AActor.
* Class that represents a rooms door.
*/
UCLASS()
class PROTUX_API ADoor : public AActor
{
	GENERATED_BODY()
	
#pragma region Properties

public:	

	/* Boolean indicating if the door is open. */
	UPROPERTY(BlueprintReadWrite, Category = "Door")
		bool bOpenDoor;

	/* Boolean indicating if the door is closed. */
	UPROPERTY(BlueprintReadWrite, Category = "Door")
		bool bCloseDoor;

	/* Boolean indicating if the door is locked. */
	UPROPERTY(BlueprintReadWrite, Category = "Door")
		bool bIsDoorLocked;

	/* Pointer to the parent room of the door. */
	UPROPERTY(BlueprintReadWrite, Category = "Room")
	class ARoom* ParentRoom;

#pragma endregion Properties

#pragma  region Constructor

	/* Standard Constructor */
	ADoor();

#pragma endregion Constructor

#pragma region Functions

public:

	/*
	* Event triggered to lock the door.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Lock Door", Keywords = "Lock Door"), Category = "Door")
		void LockDoor();

	/*
	* Event triggered to unlock the door.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Unlock Door", Keywords = "Unlock Door"), Category = "Door")
		void UnlockDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
#pragma endregion Functions
	
};
