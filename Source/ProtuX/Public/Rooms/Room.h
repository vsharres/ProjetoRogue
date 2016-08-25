// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.h"
#include "Room.generated.h"

/**
* Enum that represents the difficulty of the room.
*/
UENUM(BlueprintType)
enum class ERoomDifficulty : uint8
{
	NORMAL,
	HARD

};
/**
* Enum with the number of doors that the rooms has.
*/
UENUM(BlueprintType)
enum class ENumberDoors : uint8
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
};

/**
* Enum for each room shape, necessary to calculate the position of the doors.
*/
UENUM(BlueprintType)
enum class ERoomShape : uint8
{
	Default,
	LEFT,
	RIGHT

};

/**
* Enum representing the type of room.
*/
UENUM(BlueprintType)
enum class ERoomType : uint8
{
	NORMAL,
	START,
	ITEM,
	KEY,
	BOSS

};

/**
*	Class inherited from AActor.
*	Class that represents a room in the game. A room can be also special rooms, such as the Key, start and boos rooms.
*	A Default room is one with only one door in the WEST configuration.
*/
UCLASS()
class PROTUX_API ARoom : public AActor
{
	GENERATED_BODY()

#pragma region Properties

protected:

	/** Room direction,which is the direction of its first door. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomShape RoomDirection;

	/** Room type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomType RoomType;

	/** Room difficulty. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomDifficulty Difficulty;

	/** Room Scale. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		FVector RoomScale;

	/** Room Offset. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		float RoomOffset;

	/** Collision component, which is triggered when the player enters the room, and its enemies are activated. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerEnemiesActivate;

	/** Number of doors in the room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
		ENumberDoors NumberDoors;

	/** Doors array. */
	UPROPERTY(BlueprintReadWrite, Category = "Door")
		TArray<class ADoor*> Doors;

	/** Doors direction array, the index of this array is always the same as in the Doors arrays. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		TArray < TEnumAsByte<EDoorDirection> > DoorsDirArray;

	/** Array of enemies in the room. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
		TArray<class AEnemy*> Enemies;

	/** Array of classes of normal enemies in the room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		TArray<TSubclassOf<AEnemy>> ListEnemiesNormal;

	/** Array of classes of hard enemies in the room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		TArray<TSubclassOf<AEnemy>> ListEnemiesHard;

	/** Array of items classes that can be spawned in the room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		TArray<TSubclassOf<class UItem>> PossibleItems;

public:

	/** Boolean indicating if the room stil has enemies. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		bool bRoomHasEnemies;

	/** Array of connected rooms to this room. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
		TArray<ARoom*> ConectedRooms;

	/** Boolen indicating if the room was visited during generation, used only during generation. */
	UPROPERTY(BlueprintReadWrite, Category = "Room")
		bool bVisited;

#pragma endregion Properties

#pragma region Constructor

public:
	/** Default Constructor. */
	ARoom(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

public:

	/**
	* Get Function of room scale.
	* @return FVector value of the room scale.
	*/
	UFUNCTION()
		FVector GetRoomScale() const;

	/**
	* Get function with the room offset.
	* @return float offset value
	*/
	UFUNCTION()
		float GetRoomOffset() const;

	/**
	* Get function for the number of doors.
	* @return Enum value of the number of doors.
	*/
	UFUNCTION()
		ENumberDoors GetNumDoors() const;

	/**
	* Get function for the room shape.
	* @return Enum value with the room shape.
	*/
	UFUNCTION()
		ERoomShape GetRoomShape() const;

	/**
	* Função Get do tipo da sala.
	* @return Enumerador ETipoSala com o tipo da sala.
	*/
	UFUNCTION()
		ERoomType GetRoomType() const;

	/**
	* Get function for the array of doors.
	* @return TArray<TEnumAsByte<EDirecaoPorta>> value with the array of doors.
	*/
	UFUNCTION()
		TArray<TEnumAsByte<EDoorDirection>> GetArrayDoors();

	/**
	* Set function for the offset.
	* @param newOffset - float value of the new offset.
	*/
	UFUNCTION()
		void SetOffset(float newOffset);

	/**
	* Event to deactivate the trigger, used when all of the enemies in the room are defeated.
	*/
	UFUNCTION()
		void DeactivateTrigger();

	/**
	* Function that is used to remove a single enemy from the enemy array.
	* @param enemy - Pointer to the enemy to be removed.
	*/
	UFUNCTION()
		void RemoveEnemy(AEnemy* enemy);

	/**
	* Event triggered to spawn enemies in the room.
	* This event is implemented by Blueprint scripts to define specific behaviors to special rooms.
	* @param Stream - Random generation stream. 
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Spawn Enemy", Keywords = "Spawn Enemy"), Category = "Enemy")
		void SpawnEnemies(FRandomStream& Stream);
	virtual void SpawnEnemies_Implementation(FRandomStream& Stream);

	/**
	* Get function of the type of enemy to be spawned for a specific seed.
	* The resulting type is chosen randomly using the specified seed.
	* @param EnemyClassArray - Array of enemies classes that can be spawned.
	* @param Stream - Random generation stream.
	* @return TSubclassOf<AEnemy> enemy class pointer.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Enemy Type", Keywords = "Get Enemy Type"), Category = "Enemy")
		TSubclassOf<AEnemy> GetEnemyType(const TArray <TSubclassOf<AEnemy>>& EnemyClassArray,FRandomStream& Stream);

	/**
	* Event triggered when all enemies in the room are defeated.
	*/
	UFUNCTION()
		void OnEnemiesDefeated();

	/**
	* Function to lock all doors in the room.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Lock Doors", Keywords = "Lock Doors"), Category = "Room")
		void LockDoors();

	/**
	* Function to unlock all doors in the room.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Portas", Keywords = "Destrancar Portas"), Category = "Room")
		void UnlockDoors();
	/**
	* Event to trigger the elevator in the 
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Activate Elevator", Keywords = "Activate Elevator"), Category = "Room")
		void ActivateElevator();

	/**
		Event to update enemies health bar.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Room")
		void UpdateEnemiesHealth(AProtuXPlayer* player);

	/**
	* On overlap event for the activate enemies trigger.
	*/
	UFUNCTION(BlueprintCallable, Category = Room)
		void ActivateEnemiesTriggerOnOverlap(class AActor* OtherActor);

	/**
	* End overlap event for the activate enemies trigger.
	*/
	UFUNCTION(BlueprintCallable, Category = Room)
		 void ActivateEnemiesTriggerEndOverlap(class AActor* OtherActor);

	/**
	* Function to change the colors of the light bars in the room showing when enemies are defeated.
	* @param newColor - New color of the lights.
	* @param roomLights - The room lights components in the room.
	*/
	UFUNCTION(BlueprintCallable, Category = Glow)
		void ChangeRoomColor(FLinearColor newColor, USceneComponent* roomLights);

	/**
	* Called every frame.
	*/
	virtual void Tick(float DeltaTime) override;

#pragma endregion Functions

};
