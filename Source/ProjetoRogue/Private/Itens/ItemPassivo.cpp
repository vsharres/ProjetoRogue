// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemPassivo.h"
#include "Public/Jogador/Jogador.h"

UItemPassivo::UItemPassivo()
{
	Tipo = ETipoItem::PASSIVO;
	Stats = FItemStats();
}

void UItemPassivo::AplicarItem()
{
	if (Jogador->IsValidLowLevelFast())
	{
		Jogador->ItensPassivos.Add(this);

		Super::AplicarItem();
	}
}

void UItemPassivo::RemoverItem()
{
	if (Jogador->IsValidLowLevelFast())
	{
		Jogador->ItensPassivos.Remove(this);

		Super::RemoverItem();
	}
	
}



