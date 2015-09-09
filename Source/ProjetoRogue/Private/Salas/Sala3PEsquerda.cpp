// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala3PEsquerda.h"

ASala3PEsquerda::ASala3PEsquerda(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	DirecaoPortas.Add(EDirecaoPorta::LESTE);
}

