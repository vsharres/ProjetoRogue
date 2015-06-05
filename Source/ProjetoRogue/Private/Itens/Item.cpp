// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/Item.h"
#include "Public/Jogador/Jogador.h"

UItem::UItem()
{
	Stats = FItemStats();
}

void UItem::AplicarStats()
{
	Jogador->Stats += Stats;
}

void UItem::RemoverStats()
{
	Jogador->Stats -= Stats;
}

void UItem::AplicarItem()
{
	AplicarStats();
}

void UItem::RemoverItem()
{
	RemoverStats();

	this->BeginDestroy();
}

UObject* UItem::InstanciarItem(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		UObject* temp = StaticConstructObject(Classe);

		return temp;
	}

	return NULL;

}


