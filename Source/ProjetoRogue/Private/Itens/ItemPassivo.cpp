// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemPassivo.h"
#include "Jogador.h"

UItemPassivo::UItemPassivo()
{
	Tipo = ETipoItem::PASSIVO;
}

void UItemPassivo::AplicarItem_Implementation()
{
	if (Jogador)
	{
		Jogador->ItensPassivos.Add(this);

		Super::AplicarItem_Implementation();
	}
}

void UItemPassivo::RemoverItem_Implementation()
{
	if (Jogador)
	{
		Jogador->ItensPassivos.Remove(this);

		Super::RemoverItem_Implementation();
	}
	
}



