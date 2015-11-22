// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemPassivo.h"
#include "Jogador.h"

UItemPassivo::UItemPassivo()
{
	//Inicializando propriedades
	Tipo = ETipoItem::PASSIVO;
}

void UItemPassivo::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast()) //checando se o jogador é valido
	{
		Jogador->ItensPassivos.Add(this); //adicionando o item ao array de itens passivos do jogador

		Super::AplicarItem_Implementation(); //aplicar o item
	}
}

void UItemPassivo::RemoverItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast()) //checar se o jogador é valido
	{
		Jogador->ItensPassivos.Remove(this); //remover o item do array de itens passivos do jogador.

		Super::RemoverItem_Implementation(); //remover o items
	}
	
}



