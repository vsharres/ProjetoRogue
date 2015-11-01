// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "DanoInterface.h"

UDanoInterface::UDanoInterface(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

}

void IDanoInterface::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{

}

void IDanoInterface::AplicarStatsProjetil(AProjectil* projetil)
{

}
