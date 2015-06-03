// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala3P.h"


ASala3P::ASala3P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	bVisitada = false;
}

