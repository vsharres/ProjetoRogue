// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemProjetil.h"
#include "Projectil.h"

UItemProjetil::UItemProjetil()
{
	Tipo = ETipoItem::PROJETIL;
}

void UItemProjetil::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast() && Jogador->ProjetilAtual != this)
	{
		if (Jogador->ProjetilAtual->IsValidLowLevelFast() && this->Projetil->IsValidLowLevelFast())
		{
			Jogador->ProjetilAtual->RemoverItem();
			Jogador->ProjetilAtual = this;

		}
		else if (Jogador->ProjetilAtual->IsValidLowLevelFast() && !this->Projetil->IsValidLowLevelFast())
		{
			this->Projetil = Jogador->ProjetilAtual->Projetil;
			Jogador->ProjetilAtual = this;
		}
		else
		{
			Jogador->ProjetilAtual = this;
		}
	}

	Super::AplicarItem_Implementation();
}

void UItemProjetil::RemoverItem_Implementation()
{
	Super::RemoverItem_Implementation();
}

