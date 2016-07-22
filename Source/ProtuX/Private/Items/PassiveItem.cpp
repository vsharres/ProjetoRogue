// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "PassiveItem.h"
#include "ProtuXPlayer.h"

UPassiveItem::UPassiveItem()
{
	//Inicializando propriedades
	Type = EItemType::PASSIVE;
}

void UPassiveItem::ApplyItem_Implementation()
{
	if (Player->IsValidLowLevelFast()) //checando se o jogador é valido
	{
		Player->PassiveItems.Add(this); //adicionando o item ao array de itens passivos do jogador

		Super::ApplyItem(); //aplicar o item
	}
}

void UPassiveItem::RemoveItem_Implementation()
{
	if (Player->IsValidLowLevelFast()) //checar se o jogador é valido
	{
		Player->PassiveItems.Remove(this); //remover o item do array de itens passivos do jogador.

		Super::RemoveItem(); //remover o items
	}
	
}



