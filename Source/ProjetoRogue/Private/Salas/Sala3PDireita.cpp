// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala3PDireita.h"

ASala3PDireita::ASala3PDireita()
{
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EDirecaoSala::DIREITA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::SUL);
	DirecaoPortas.Add(EDirecaoPortas::LESTE);
}




