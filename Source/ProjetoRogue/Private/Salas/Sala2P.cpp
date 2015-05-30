// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2P.h"

ASala2P::ASala2P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EDirecaoSala::NORMAL;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::LESTE);
	bVisitada = false;
}


