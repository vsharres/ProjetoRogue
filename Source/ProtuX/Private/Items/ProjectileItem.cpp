// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProjectileItem.h"
#include "Projectile.h"

UProjectileItem::UProjectileItem()
{
	//Initializing properties
	Type = EItemType::PROJECTILE;
	bIsActive = false;
	bIsStandardProjectile = false;
	EnergyRequired = 1.0f;
}

void UProjectileItem::ApplyItem_Implementation()
{
	if (Player->IsValidLowLevelFast() && this->bIsStandardProjectile)
	{
		Player->CurrentProjectile = this;
	}
	else 
	{
		Player->FoundProjectile = this->GetClass();
	}
}

void UProjectileItem::RemoveItem_Implementation()
{
	this->ConditionalBeginDestroy();
}

void UProjectileItem::ActivateItem_Implementation()
{
	//if player's energy is more than the energy required, the projectile item is active
	if (Player->Stats.Energy >= EnergyRequired) 
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

