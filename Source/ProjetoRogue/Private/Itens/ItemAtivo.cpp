// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemAtivo.h"
#include "Public/Jogador/Jogador.h"

UItemAtivo::UItemAtivo()
{
	Tipo = ETipoItem::ATIVO;
	bAtivo = false;
}

void UItemAtivo::AtivarItem_Implementation()
{
	bAtivo = true;
	Super::AplicarStats();

}

void UItemAtivo::DesativarItem_Implementation()
{
	bAtivo = false;
	Super::RemoverStats();
}


void UItemAtivo::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast())
	{
		if (Jogador->ItemAtivoAtual->IsValidLowLevelFast())
		{
			Jogador->ItemAtivoAtual->RemoverItem();
			Jogador->ItemAtivoAtual = this;
		}
		else
		{
			Jogador->ItemAtivoAtual = this;
		}
	}
}

void UItemAtivo::RemoverItem_Implementation()
{
	this->BeginDestroy();
}


