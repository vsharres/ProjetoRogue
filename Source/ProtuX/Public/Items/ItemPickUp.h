// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#pragma once

#include "Items/PickUp.h"
#include "ItemPickUp.generated.h"

/**
 * Class inherited from APickUp
 * Class responsible for spawning items drop by the boss
 */
UCLASS()
class PROTUX_API AItemPickUp : public APickUp
{
	GENERATED_BODY()

#pragma region Properties

protected:

	/** Class array with all possible items */
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		TArray<TSubclassOf<class UItem>> PossibleItems;

public:

	/** Pointer to the Item spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UItem* SpawnedItem;

	/** Class of the item to be spawned */
	UPROPERTY(EditAnywhere, Category = "Item")
		TSubclassOf<UItem> ItemToSpawn;

#pragma endregion Properties

#pragma region Constructor

	/** Default Constructor */
	AItemPickUp(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor

#pragma region Functions

	/**
	* Function to choose randomly an item to spawn.
	* @param Stream - Random stream generator
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		void ChooseItem(FRandomStream& Stream);

	/**
	* Delegate function to be executed when the collider overlaps with the player
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
