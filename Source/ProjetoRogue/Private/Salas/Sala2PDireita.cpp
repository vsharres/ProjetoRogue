// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2PDireita.h"

ASala2PDireita::ASala2PDireita()
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EFormatoSala::DIREITA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
}


