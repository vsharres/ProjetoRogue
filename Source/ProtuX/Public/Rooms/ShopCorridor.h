// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rooms/Corridor.h"
#include "ShopCorridor.generated.h"

/* Enum representing the type of slot in the shop. */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	ENERGY,
	HEALTH,
	ITEM

};

/* Struct that stores the properties of a given shop item slot.*/
USTRUCT()
struct FShopSlot{

	GENERATED_USTRUCT_BODY()

	/* Cost of the item in the slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopSlot Struct")
		int32 Cost;

	/* Effect provided by the item in the slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopSlot Struct")
		float Effect;

	/* Type of item in the slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopSlot Struct")
		ESlotType Type;

	/* Pointer to the item in the slot. This variable is only valid if the type of slot is of type ESlotTipo::ITEM */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopSlot Struct")
	class UItem* Item;

	/* Boolean indicating if the slot was bought. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopSlot Struct")
		bool bBought;

	/* Standard Constructor */
	FShopSlot() : Cost(10),
		Effect(0),
		Type(ESlotType::ENERGY),
		Item(NULL),
		bBought(false)
	{}

	/* Destructor */
	~FShopSlot()
	{
		Item = NULL;
	}

};

/**
* Class inherited from ACorridor.
* This Class represents a special type of corridor that has a shop in it. On a shop the player can buy items, health and energy packs.
*/
UCLASS()
class PROTUX_API AShopCorridor : public ACorridor
{
	GENERATED_BODY()

#pragma region Properties

private:

	/* Corridor root component. Used as the corridor transform.*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Root")
		USceneComponent* ShopCorridorRoot;

	/* Collision trigger component that activates the shop. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Trigger")
		UBoxComponent* ShopTrigger;

	/* Array with all possible item classes that can be in a slot in the shop. */
	UPROPERTY(EditDefaultsOnly, Category = "Itens")
		TArray<TSubclassOf<UItem>> Items;


public:

	/* Shop slots array. The standard number of slots is 3 slots. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
		TArray<FShopSlot> Slots;

#pragma endregion

#pragma region Constructor

	/* Standard Constructor */
	AShopCorridor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Functions

	/* Event called when the game begins, initialize variables. */
	void BeginPlay() override;

	/*
	* Function used to initialize the shop, populating the slots with items.
	*/
	UFUNCTION()
		void InitializeShop();
	/*
	* Function to buy a slot.
	* @param slot - Index of the slot in the shop (0 to 2).
	* @param player - Pointer to the player.
	*/
	UFUNCTION(BlueprintCallable, Category = "Shop")
		void BuySlot(int32 slot, class AProtuXPlayer* player);

	/* Function to save the Shop. This function is always called after the player has bought a slot. */
	UFUNCTION(BlueprintCallable, Category = "Shop")
		void SaveShopState();

	/* Function to load a shop from a save game. */
	UFUNCTION(BlueprintCallable, Category = "Shop")
		void LoadShopState();

#pragma endregion

};
