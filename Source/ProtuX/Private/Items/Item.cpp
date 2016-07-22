// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Item.h"
#include "ProtuXPlayer.h"

UItem::UItem()
{
	//Inicializando os stats do item
	Stats = FItemStats();
}

TArray<FString> UItem::GetEffectsNames()
{
	TArray<FString> toReturn;

	//Criar o array com o nome dos stats que são modificados pelo item
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

	//Criar o array com o valor das propriedades que são alteradas pelo item
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
		Stats = Player->Stats.ClampAddStats(Stats); //aplicar os stats do item ao jogador, levando em consideração os limites dos stats.
		ApplyItem();
	}
}

void UItem::ApplyStats()
{
	Player->Stats += Stats; //aplicar os stats
	Player->UpdateProjectileStats(); //checar os limites 
}

void UItem::RemoveStats()
{
	Player->Stats -= Stats; //remover os stats
	Player->UpdateProjectileStats(); //checar os limites 
}

void UItem::ApplyItem_Implementation()
{
	ApplyStats();
}

void UItem::RemoveItem_Implementation()
{
	RemoveStats();

	this->ConditionalBeginDestroy(); //destuir o item
}

UObject* UItem::InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine) //checar o ponteiro da instancia do jogo
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		//spawn do item
		UObject* temp = NewObject<UObject>(World,Classe);

		return temp;
	}

	return NULL;

}


