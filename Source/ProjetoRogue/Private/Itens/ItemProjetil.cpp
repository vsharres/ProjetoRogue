// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemProjetil.h"
#include "Projectil.h"

UItemProjetil::UItemProjetil()
{
	Tipo = ETipoItem::PROJETIL;
	bAtivo = false;
	bProjetilPadrao = false;
	EnergiaUtilizada = 1.0f;
}

void UItemProjetil::AplicarItem_Implementation()
{
	/*if (Jogador->IsValidLowLevelFast() && this->bProjetilPadrao)
	{
		Jogador->ProjetilAtual = this;
	}
	else if (Jogador->IsValidLowLevelFast() && Jogador->ProjetilEncontrado->IsValidLowLevelFast() && !this->bProjetilPadrao)
	{
		Jogador->ProjetilEncontrado->RemoverItem();
		Jogador->ProjetilEncontrado = this;
	}
	else if (!this->bProjetilPadrao)
	{
		Jogador->ProjetilEncontrado = this;
	}*/
}

void UItemProjetil::RemoverItem_Implementation()
{
	this->BeginDestroy();
}

void UItemProjetil::AtivarItem_Implementation()
{
	if (Jogador->Stats.Energia >= EnergiaUtilizada)
	{
		bAtivo = true;
		Super::AplicarStats();
	}

}

void UItemProjetil::DesativarItem_Implementation()
{
	bAtivo = false;
	Super::RemoverStats();
}

