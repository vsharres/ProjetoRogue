// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala4P.h"

ASala4P::ASala4P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumeroPortas = ENumeroPortas::QUATRO;
	DirecaoSala = EDirecaoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::NORTE);
	DirecaoPortas.Add(EDirecaoPortas::LESTE);
	DirecaoPortas.Add(EDirecaoPortas::SUL);
	bVisitada = false;
}


