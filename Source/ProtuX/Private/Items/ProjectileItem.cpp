// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProjectileItem.h"
#include "Projectile.h"

UProjectileItem::UProjectileItem()
{
	//Inicializando as propriedades
	Type = EItemType::PROJECTILE;
	bIsActive = false;
	bIsStandardProjectile = false;
	EnergyRequired = 1.0f;
}

void UProjectileItem::ApplyItem_Implementation()
{
	if (Player->IsValidLowLevelFast() && this->bIsStandardProjectile) //checar que o jogador é valido
	{
		Player->CurrentProjectil = this;
	}
	else 
	{
		Player->FoundProjectil = this->GetClass();
	}
}

void UProjectileItem::RemoveItem_Implementation()
{
	this->ConditionalBeginDestroy(); //Destruir o item
}

void UProjectileItem::ActivateItem_Implementation()
{
	if (Player->Stats.Energy >= EnergyRequired) //se a energia do jogador é maior do que a energia utilizado pelo item, o item pode ser ativado
	{
		bIsActive = true;
		Super::ApplyStats();
	}

}

void UProjectileItem::DeactivateItem_Implementation()
{
	bIsActive = false;
	Super::RemoveStats();
}

