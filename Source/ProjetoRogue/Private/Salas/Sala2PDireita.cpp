// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2PDireita.h"

ASala2PDireita::ASala2PDireita()
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EDirecaoSala::DIREITA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	DirecaoPortas.Add(EDirecaoPortas::SUL);
}


