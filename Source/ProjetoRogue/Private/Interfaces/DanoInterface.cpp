// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "DanoInterface.h"

UDanoInterface::UDanoInterface(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	//CONSTRUTOR PADR�O
}

void IDanoInterface::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	//FUN��O VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}

void IDanoInterface::AplicarStatsProjetil(AProjectil* projetil)
{
	//FUN��O VIRTUAL, SOBRE OVERRIDE DE CLASSES QUE POSSUEM A INTERFACE
}
