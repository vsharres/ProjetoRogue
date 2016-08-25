// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ProjectileItem.generated.h"

/**
* Class inherited from UItem
* Class which represents a projectile item, which represents the item responsible for the player's shot. Projectile items are activated by the player explicitly.
* 
*/
UCLASS()
class PROTUX_API UProjectileItem : public UItem
{
	GENERATED_BODY()

#pragma region Properties
public:

	/** Boolean value indicating if the projectile is active */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bIsActive;

	/** Boolean value indicating if the projectile is a standard projectile(if the item is the one the player begins the game with) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		bool bIsStandardProjectile;

	/** How much energy is consumed by the time per tick */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float EnergyRequired;

	/** Class of the projectile to be spawn on firing */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		TSubclassOf<class AProjectile> Projectile;

	/** Cannon damage mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMesh* CannonDamageMesh;

	/** Material instance of the Cannon damage mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UMaterialInstance* CannonDamageMaterial;

	/** Cannon accuracy mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMesh* CannonAccuracyMesh;

	/** Material instance of the cannon accuracy mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UMaterialInstance* CannonAccuracyMAterial;

	/** Cannon fire rate mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMesh* CannonFireRateMesh;

	/** Material instance of the cannon fire rate mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UMaterialInstance* CannonFireRateMaterial;

#pragma endregion Properties

	
#pragma region Constructor

	/** Default Constructor */
	UProjectileItem();

#pragma endregion Constructor

#pragma region Functions

	/**
	* Function to activate the item
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Activate Item", Keywords = "Activate item"), Category = "Item")
		void ActivateItem();
	virtual void ActivateItem_Implementation();

	/**
	* Function to deactivate the item
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Deactivate Item", Keywords = "Deactivate item"), Category = "Item")
		void DeactivateItem();
	virtual void DeactivateItem_Implementation();

	/**
	* Override of the apply item function
	*/
	virtual void ApplyItem_Implementation() override;

	/**
	* Override of the remove item function
	*/
	virtual void RemoveItem_Implementation() override;

#pragma endregion Functions

};
