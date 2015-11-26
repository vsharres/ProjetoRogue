// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala3PDireita.h"

ASala3PDireita::ASala3PDireita(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::DIREITA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
	DirecaoPortas.Add(EDirecaoPorta::LESTE);
}




