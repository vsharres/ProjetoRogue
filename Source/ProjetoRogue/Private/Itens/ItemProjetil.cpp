// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemProjetil.h"
#include "Public/Projeteis/Projectil.h"

UItemProjetil::UItemProjetil()
{
	Tipo = ETipoItem::PROJETIL;
}

void UItemProjetil::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast() && Jogador->ProjetilAtual != this)
	{
		if (Jogador->ProjetilAtual->IsValidLowLevelFast())
		{
			Jogador->ProjetilAtual->RemoverItem();
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

