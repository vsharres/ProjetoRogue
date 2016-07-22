// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "DamageInterface.h"

UDamageInterface::UDamageInterface(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	//Constructor PADR�O
}

void IDamageInterface::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	//FUN��O VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}

void IDamageInterface::ApplyProjectileStats(AProjectile* projectile)
{
	//FUN��O VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}
