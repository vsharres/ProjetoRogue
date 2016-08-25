// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

/**
* Enum of the type of item, it can be a passive or a projectile item
*/
UENUM(BlueprintType)
enum class EItemType : uint8
{
	PASSIVE,
	PROJECTILE
};

/**
* Struct that holds the stats of a given item
*/
USTRUCT()
struct FItemStats
{
	GENERATED_USTRUCT_BODY()

		/** How much the item increases the player's current health */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddHealth;

	/** How much the item increases the player's max health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMaxHealth;

	/** How much the item increases the player's movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddSpeed;

	/** How much the item increases the player's fire rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddFireRate;

	/** How much the item increases the damage dealt by the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddDamage;

	/** How much the item increases the player's accuracy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddAccuracy;

	/** How much the item increases the projectile's speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMuzzleSpeed;

	/** How much the item increases the player's current energy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddEnergy;

	/** How much the item increases the player's max energy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMaxEnergy;


	/**
	* Overload of the add and assign operator, to facilitate adding the stats of one item to another
	* @param itemStats - Ref to the item to be added
	* @return Ref to the modified item
	*/
	FORCEINLINE	FItemStats& operator+=(const FItemStats& itemStats)
	{
		this->AddHealth += itemStats.AddHealth;
		this->AddMaxHealth += itemStats.AddMaxHealth;
		this->AddSpeed += itemStats.AddSpeed;
		this->AddFireRate += itemStats.AddFireRate;
		this->AddDamage += itemStats.AddDamage;
		this->AddAccuracy += itemStats.AddAccuracy;
		this->AddMuzzleSpeed += itemStats.AddMuzzleSpeed;
		this->AddEnergy += itemStats.AddEnergy;
		this->AddMaxEnergy += itemStats.AddMaxEnergy;

		return *this;

	}

	/** Default Constructor */
	FItemStats(float addHealthMax = 0.0f, float addHealth = 0.0f,
		float addSpeed = 0.0f, float addFireRate = 0.0f,
		float addDamage = 0.0f, float addAccuracy = 0.0f,
		float addMuzzleSpeed = 0.0f, float addEnergy = 0, float addMaxEnergy = 0)
	{
		AddMaxHealth = addHealthMax;
		AddHealth = addHealth;
		AddSpeed = addSpeed;
		AddFireRate = addFireRate;
		AddDamage = addDamage;
		AddAccuracy = addAccuracy;
		AddMuzzleSpeed = addMuzzleSpeed;
		AddEnergy = addEnergy;
		AddMaxEnergy = addMaxEnergy;
	}


};

/**
* Abstract class that represents an item that the player can collect. 
* An item can be either passive, where its effects is constant, or an projectile item where the effect is only applied when activated.
* To use an projectile item, energy is consumed on a given rate.
*/
UCLASS(BlueprintType, Blueprintable, abstract)
class PROTUX_API UItem : public UObject
{
	GENERATED_BODY()

#pragma region Properties
public:

	/** Item stats */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FItemStats Stats;

	/** Item type */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		EItemType Type;

	/** Weak pointer to the player */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		TWeakObjectPtr<class AProtuXPlayer> Player;

	/** Item name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName ItemName;

	/** Description of the effects caused by the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FText EffectsDescription;

	/** Cost to purchase the item at the shop */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		int32 Cost;

#pragma endregion Properties

#pragma region Constructor
public:

	/** Default Constructor */
	UItem();

#pragma endregion Constructor

#pragma region Functions
public:

	/**
	* Get function to access an array with the description of the effects caused by the item. This function is used by the game UI
	* @return Strings array with the descriptions of each effect
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<FString> GetEffectsNames();

	/**
	* Get function to access an array with the value of each of the effects caused by the item. This function is used by the game UI
	* @return float array with the values of each effect
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<float> GetEffects();

	/**
	* Function to initialize an item.
	* @param initializer - Pointer to the player that initialized the item
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init Item", Keywords = "Initialize Item"), Category = "Item")
		void InitializeItem(AProtuXPlayer* initializer);

	/**
	* Function to apply the stats of the item on the player
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Stats", Keywords = "Apply Stats"), Category = "Item")
		void ApplyStats();

	/**
	* Function to remove the stats of the item from the player
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove Stats", Keywords = "Remove Stats"), Category = "Item")
		void RemoveStats();

	/**
	* Function to apply an item to the player
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Apply Item", Keywords = "Apply item"), Category = "Item")
		void ApplyItem();
	virtual void ApplyItem_Implementation();

	/**
	* Function to remove an item from the player
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Remove Item", Keywords = "Remove item"), Category = "Item")
		void RemoveItem();
	virtual void RemoveItem_Implementation();

	/**
	* Static function to instantiate a new item in a Blueprint script
	* @param WorldContextObject - Pointer to the world context of the blueprint
	* @param Classe - Class of the item to be instantiated
	*/
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instanciar Item", Keywords = "Instanciar item"), Category = Item)
		static UObject* InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe);

#pragma endregion Functions

};
