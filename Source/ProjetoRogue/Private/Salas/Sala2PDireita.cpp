// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala2PDireita.h"

ASala2PDireita::ASala2PDireita(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EFormatoSala::DIREITA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
}


