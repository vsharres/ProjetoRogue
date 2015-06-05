// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemAtivo.h"
#include "Public/Jogador/Jogador.h"

UItemAtivo::UItemAtivo()
{
	Tipo = ETipoItem::ATIVO;
	Stats = FItemStats();
	bAtivo = false;
}

void UItemAtivo::AtivarItem()
{
	bAtivo = true;
	Super::AplicarStats();

}

void UItemAtivo::DesativarItem()
{

	bAtivo = false;
	Super::RemoverStats();

}


void UItemAtivo::AplicarItem()
{
	if (Jogador->IsValidLowLevelFast())
	{
		if (Jogador->AtivoAtual->IsValidLowLevelFast())
		{
			Jogador->AtivoAtual->RemoverItem();
			Jogador->AtivoAtual = this;
		}
		else
		{
			Jogador->AtivoAtual = this;
		}
	}
}

void UItemAtivo::RemoverItem()
{
	Super::RemoverItem();
}


