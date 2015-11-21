// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala3P.h"


ASala3P::ASala3P(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	bVisitada = false;
}

