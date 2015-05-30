// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2PEsquerda.h"

ASala2PEsquerda::ASala2PEsquerda()
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EDirecaoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::NORTE);

}




