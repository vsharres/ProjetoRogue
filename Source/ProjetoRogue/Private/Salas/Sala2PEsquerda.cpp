// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2PEsquerda.h"

ASala2PEsquerda::ASala2PEsquerda()
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EFormatoSala::ESQUERDA;
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);

}




