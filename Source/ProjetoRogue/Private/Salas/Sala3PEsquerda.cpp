// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala3PEsquerda.h"

ASala3PEsquerda::ASala3PEsquerda()
{
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EDirecaoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::NORTE);
	DirecaoPortas.Add(EDirecaoPortas::LESTE);
}




