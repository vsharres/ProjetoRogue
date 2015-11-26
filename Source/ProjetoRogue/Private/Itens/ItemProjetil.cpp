// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemProjetil.h"
#include "Projectil.h"

UItemProjetil::UItemProjetil()
{
	//Inicializando as propriedades
	Tipo = ETipoItem::PROJETIL;
	bAtivo = false;
	bProjetilPadrao = false;
	EnergiaUtilizada = 1.0f;
}

void UItemProjetil::AplicarItem_Implementation()
{
	if (Jogador->IsValidLowLevelFast() && this->bProjetilPadrao) //checar que o jogador é valido
	{
		Jogador->ProjetilAtual = this;
	}
	else 
	{
		Jogador->ProjetilEncontrado = this->GetClass();
	}
}

void UItemProjetil::RemoverItem_Implementation()
{
	this->ConditionalBeginDestroy(); //Destruir o item
}

void UItemProjetil::AtivarItem_Implementation()
{
	if (Jogador->Stats.Energia >= EnergiaUtilizada) //se a energia do jogador é maior do que a energia utilizado pelo item, o item pode ser ativado
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

