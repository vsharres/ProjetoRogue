// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "DamageInterface.h"

UDamageInterface::UDamageInterface(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	//Default constructor is needed for to compile project, but no implementation
}

void IDamageInterface::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	//VIRTUAL FUNCTION, NO BASIC IMPLEMENTATION
}

void IDamageInterface::ApplyProjectileStats(AProjectile* projectile)
{
	//VIRTUAL FUNCTION, NO BASIC IMPLEMENTATION
}
