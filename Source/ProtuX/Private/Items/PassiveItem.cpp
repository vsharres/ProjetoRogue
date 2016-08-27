// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "PassiveItem.h"
#include "ProtuXPlayer.h"

UPassiveItem::UPassiveItem()
{
	//Initializing properties
	Type = EItemType::PASSIVE;
}

void UPassiveItem::ApplyItem_Implementation()
{
	if (Player->IsValidLowLevelFast())
	{
		//Adding item to the passive items array
		Player->PassiveItems.Add(this); 

		Super::ApplyItem(); //calling parent function
	}
}

void UPassiveItem::RemoveItem_Implementation()
{
	if (Player->IsValidLowLevelFast()) 
	{
		//remove item from the passive items array
		Player->PassiveItems.Remove(this); 

		Super::RemoveItem(); //calling parent function
	}
	
}



