// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemProjetil.h"
#include "Public/Projeteis/Projectil.h"

UItemProjetil::UItemProjetil()
{
	Tipo = ETipoItem::PROJETIL;
}

void UItemProjetil::Atirar_Implementation()
{

}

void UItemProjetil::AplicarItem_Implementation()
{
	Super::AplicarItem();
}

void UItemProjetil::RemoverItem_Implementation()
{
	Super::RemoverItem();
}





