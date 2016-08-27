// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Item.h"
#include "ProtuXPlayer.h"

UItem::UItem()
{
	//Initializing item stats
	Stats = FItemStats();
}

TArray<FString> UItem::GetEffectsNames()
{
	TArray<FString> toReturn;

	//Generating array with the name of the stats that are modified by the item
	if (Stats.AddDamage != 0.0f)
	{
		toReturn.Add("Damage");
	}

	if (Stats.AddEnergy != 0)
	{
		toReturn.Add("Energy");
	}

	if (Stats.AddMaxEnergy != 0)
	{
		toReturn.Add("Max Energy");
	}

	if (Stats.AddFireRate != 0.0f)
	{
		toReturn.Add("Fire Rate");
	}

	if (Stats.AddAccuracy != 0.0f)
	{
		toReturn.Add("Accuracy");
	}

	if (Stats.AddSpeed != 0.0f)
	{
		toReturn.Add("Speed");
	}

	if (Stats.AddMuzzleSpeed != 0.0f)
	{
		toReturn.Add("Muzzle Speed");
	}

	if (Stats.AddHealth != 0.0f)
	{
		toReturn.Add("Health");
	}

	if (Stats.AddMaxHealth != 0.0f)
	{
		toReturn.Add("Max Health");
	}

	return toReturn;

}

TArray<float> UItem::GetEffects()
{
	TArray<float> toReturn;

	//Generating the array with the value of the stats that are changed by the item
	if (Stats.AddDamage != 0.0f)
	{
		toReturn.Add(Stats.AddDamage);
	}

	if (Stats.AddEnergy != 0)
	{
		toReturn.Add(Stats.AddEnergy);
	}

	if (Stats.AddMaxEnergy != 0)
	{
		toReturn.Add(Stats.AddMaxEnergy);
	}

	if (Stats.AddFireRate != 0.0f)
	{
		toReturn.Add(Stats.AddFireRate);
	}

	if (Stats.AddAccuracy != 0.0f)
	{
		toReturn.Add(Stats.AddAccuracy);
	}

	if (Stats.AddSpeed != 0.0f)
	{
		toReturn.Add(Stats.AddSpeed);
	}

	if (Stats.AddMuzzleSpeed != 0.0f)
	{
		toReturn.Add(Stats.AddMuzzleSpeed);
	}

	if (Stats.AddHealth != 0.0f)
	{
		toReturn.Add(Stats.AddHealth);
	}

	if (Stats.AddMaxHealth != 0.0f)
	{
		toReturn.Add(Stats.AddMaxHealth);
	}

	return toReturn;
}

void UItem::InitializeItem(AProtuXPlayer* initializer)
{
	if (initializer->IsValidLowLevelFast())
	{
		this->Player = initializer;
		Stats = Player->Stats.ClampAddStats(Stats); //applying the stats to the player, clamping values
		ApplyItem();
	}
}

void UItem::ApplyStats()
{
	Player->Stats += Stats; //apply stats
	Player->UpdateProjectileStats(); //update current projectile item stats
}

void UItem::RemoveStats()
{
	Player->Stats -= Stats; //remove stats
	Player->UpdateProjectileStats();  //update current projectile item stats
}

void UItem::ApplyItem_Implementation()
{
	ApplyStats();
}

void UItem::RemoveItem_Implementation()
{
	RemoveStats();

	this->ConditionalBeginDestroy(); //destroy item
}

UObject* UItem::InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine) //checking if engine is valid
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		//Item spawn
		UObject* temp = NewObject<UObject>(World,Classe);

		return temp;
	}

	return NULL;

}


