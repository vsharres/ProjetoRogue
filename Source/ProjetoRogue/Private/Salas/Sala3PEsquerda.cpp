// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala3PEsquerda.h"

ASala3PEsquerda::ASala3PEsquerda()
{
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	DirecaoPortas.Add(EDirecaoPorta::LESTE);
}




