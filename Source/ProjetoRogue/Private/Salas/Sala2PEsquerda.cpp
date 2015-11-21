// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala2PEsquerda.h"

ASala2PEsquerda::ASala2PEsquerda(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EFormatoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);

}




