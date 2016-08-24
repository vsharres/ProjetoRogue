// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.h"
#include "RoomGenerator.generated.h"

/*
*	Class inherited from ARoom.
*	Class that represents the room generator. This class is responsible for the whole level generation.
*/
UCLASS()
class PROTUX_API ARoomGenerator : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:

	/* Number of rooms to be generated. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		int32 NumGeneratedRooms;

	/* Index where rooms with 2 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Rooms")
		int32 Room2DIndex;

	/* Index where rooms with 3 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Rooms")
		int32 Room3DIndex;

	/* Index where rooms with 4 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "3"), Category = "Rooms")
		int32 Room4DIndex;

	/* Item room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<class ARoom> ItemRoom;

	/* Key room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ARoom> KeyRoom;

	/* Boss room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ARoom> BossRoom;

	/* Corridor shop class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ACorridor> ShopCorridor;

	/* Boolean indicating if the shop corridor was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Corridor")
		bool bIsShopSpawned;

	/* Boolean indicating if the item room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bIsItemSpawned;

	/* Boolean indicating if the key room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bIsKeySpawned;

	/* Boolean indicating if the boss room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bBossSpawned;

	/* Current generated room. */
	UPROPERTY()
		TSubclassOf<ARoom> GeneratedRoom;

	/* Array with the last generated room. */
	UPROPERTY()
		TArray<TSubclassOf<ARoom>> PreviousGeneratedRooms;

	/* Array to be used during loading of the level. */
	UPROPERTY()
		TArray<bool> LoadedRooms;

	/* Max Length of the level. Which is the maximum distance a room can be from the starting room. */
	UPROPERTY(EditDefaultsOnly, Category = "Generator")
		float MaxLength;

	/* Max Width of the level. Which is the maximum distance a room can be from the starting room. */
	UPROPERTY(EditDefaultsOnly, Category = "Generator")
		float MaxWidth;

public:

	/* Array with the rooms positions. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator Rooms")
		TArray<FVector> RoomsPositions;

	/* Generator Random stream. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		FRandomStream GeneratingStream;

	/* Array with the types of rooms that can be spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
		TArray<TSubclassOf<ARoom>> TypesRooms;

	/* Array with the types of corridors that can be spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corridor")
		TArray<TSubclassOf<ACorridor>> CorridorTypes;

	/* Max number of rooms to be generated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumRooms;

	/* Minimum number of rooms to be generated.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumRooms;

	/* Random seed number. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Starting room pointer. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
		ARoom* StartingRoom;

	/* Array of rooms in the level. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		TArray<ARoom*> Rooms;

#pragma endregion Properties

#pragma region Constructor

	/*Standard Constructor.*/
	ARoomGenerator();

#pragma endregion Constructor

#pragma region Functions

public:

	/*
	* Static function to get the room generator. Function used by other classes to access the room generator.
	* @param level - Pointer to the level.
	* @return Pointer to the Room Generator.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms", meta = (WorldContext = "level", UnsafeDuringActorConstruction = "true"))
		static ARoomGenerator* GetRoomGenerator(UObject* level);

	/*
	* Initialization function for the generator, starting the level generating.
	* @param startRoom - Pointer to the starting room.
	* @param newSeed - Seed to generate.
	* @param curLevel - Current level to be generated.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void InitializeGenerator(ARoom* startRoom, int32 newSeed, int32 curLevel);

	/*
	* Get function of the relative direction between the direction of the door and its rooms.
	* @param roomDirection - Room rotation(forward vector).
	* @param door - Door direction.
	* @return Resulting rotation of the door.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		FRotator GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door);

	/*
	* Get function of the total number of empty (not connected) doors inside the array of rooms.
	* @return Total number of empty doors
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		int32 GetNumVoidDoors();

	/*
	* Function that returns the index of the last valid room in the Rooms array.
	* @return index of the last valid room.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		int32 LastValidRoom();

	/*
	* Function that generates the spawn transform for a given room.
	* @param previousRoom - Pointer to the previous room.
	* @param doorDirection - Door rotation.
	* @return FTransform of the room spawn transform.
	*/
	UFUNCTION()
		FTransform GenerateRoomTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Function that generates the spawn transform for a given corridor.
	* @param previousRoom - Pointer to the previous room.
	* @param doorDirection - Door rotation.
	* @return FTransform of the corridor spawn transform.
	*/
	UFUNCTION()
		FTransform GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Function that selects a room to be spawned, its checks for which rooms can be spawned and guarantees that special rooms will be spawned.
	* @param previousRoom - Pointer to the previous room.
	* @return class of the room to be spawned.
	*/
	UFUNCTION()
		TSubclassOf<ARoom> SelectRoom(ARoom* previousRoom);

	/*
	* Set function for the generating seed.
	* @param currentLevel - Level to calculate the new seed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void SetNumRooms(int32 currentLevel);

	/*
	* Function to add a new room to the array of rooms.
	* @param room - Pointer to the room to be added.
	*/
	UFUNCTION()
		void AddToDoorArray(ARoom* room);

	/*
	* Function that generates a new level with all rooms, corridors and spawns the enemies.
	* This function is used recursively during generation.
	* @param currentRoom - Pointer to the current Room.
	*/
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Generator Rooms")
		void GenerateLevel(ARoom* currentRoom);

	/*
	* Function that generates a Room.
	* @param previousRoom - Pointer to the previous room.
	* @param doorDirection - Rotation of the door to which the new room will be connected.
	* @return Pointer to the generated Room.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		ARoom* GenerateRoom (ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Function that generates a new Corridor.
	* @param previousRoom - Pointer to the previous room.
	* @param DirecaoPorta -  Rotation of the door to which the new corridor will be connected.
	*/
	UFUNCTION()
		void GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Function that checks for collisions with the new room with previous rooms that were already generated.
	* @param trans - transform of the new room.
	* @param doorDirection - rotation of the door to which the new room will be connected.
	*/
	UFUNCTION()
		void CheckColision(const FTransform& trans, const FRotator& doorDirection);

	/*
	* Function to generates a special room.
	*/
	UFUNCTION()
		void GenerateSpecialRoom();

	/*
	* Function that checks if a new Room has the same position than a previous room inside the Rooms array.
	* @param pos - Vector of the new position to be checked.
	* @return Boolean value of true when the new Room position is already in the array.
	*/
	UFUNCTION()
		bool InPositionArray(const FVector& pos);

	/*
	* Function that checks if a transform is colliding in a giving direction.
	* @param trans - Transform to be tested.
	* @param direction - rotation of the door to which the new room will be connected.
	* @return Boolean value of true when is colliding.
	*/
	UFUNCTION()
		bool IsCollidingToDirection(EDoorDirection direction, const FTransform& trans);

	/*
	* Event that is triggered on level generated.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Room")
		void OnLevelGenerated();

	/*
	* Function to load rooms from a save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void LoadRooms();

	/*
	* Function to save rooms in a save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void SaveRooms();
#pragma endregion Functions

};
