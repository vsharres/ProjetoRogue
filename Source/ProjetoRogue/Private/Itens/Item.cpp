// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Item.h"
#include "Jogador.h"

UItem::UItem()
{
	Stats = FItemStats();
}

void UItem::InicializarItem(AJogador* inicializador)
{
	if (inicializador->IsValidLowLevelFast())
	{
		this->Jogador = inicializador;
		AplicarItem();
	}
}

void UItem::AplicarStats()
{
	Jogador->Stats += Stats;
	Jogador->AtualizarPropriedadesComStats();
}

void UItem::RemoverStats()
{
	Jogador->Stats -= Stats;
	Jogador->AtualizarPropriedadesComStats();
}

void UItem::AplicarItem_Implementation()
{
	AplicarStats();
}

void UItem::RemoverItem_Implementation()
{
	RemoverStats();

	this->BeginDestroy();
}

UObject* UItem::InstanciarItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		UObject* temp = NewObject<UObject>(World,Classe);

		return temp;
	}

	return NULL;

}


