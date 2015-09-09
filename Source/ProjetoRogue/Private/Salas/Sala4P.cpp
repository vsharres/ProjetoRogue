// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala4P.h"

ASala4P::ASala4P(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	NumeroPortas = ENumeroPortas::QUATRO;
	DirecaoSala = EFormatoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	DirecaoPortas.Add(EDirecaoPorta::LESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
	bVisitada = false;
}

