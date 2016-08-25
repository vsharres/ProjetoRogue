// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "PassiveItem.generated.h"

/**
* Class inherited from UItem
* Class represents a passive item, where its effects give constant effects to the player, like increasing his accuracy, damage, fire rate...
*/
UCLASS()
class PROTUX_API UPassiveItem : public UItem
{
	GENERATED_BODY()

public:
#pragma region Constructor

	/** Default Constructor */
	UPassiveItem();

#pragma endregion Constructor

#pragma region Functions

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
