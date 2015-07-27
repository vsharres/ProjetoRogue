// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemPassivo.h"
#include "Public/Jogador/Jogador.h"

UItemPassivo::UItemPassivo()
{
	Tipo = ETipoItem::PASSIVO;
}

void UItemPassivo::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast())
	{
		Jogador->ItensPassivos.Add(this);

		Super::AplicarItem_Implementation();
	}
}

void UItemPassivo::RemoverItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast())
	{
		Jogador->ItensPassivos.Remove(this);

		Super::RemoverItem_Implementation();
	}
	
}



