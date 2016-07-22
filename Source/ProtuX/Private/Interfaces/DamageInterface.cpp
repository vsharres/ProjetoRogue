// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "DamageInterface.h"

UDamageInterface::UDamageInterface(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	//Constructor PADRÃO
}

void IDamageInterface::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	//FUNÇÃO VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}

void IDamageInterface::ApplyProjectileStats(AProjectile* projectile)
{
	//FUNÇÃO VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}
