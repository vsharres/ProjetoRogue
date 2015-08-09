// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala2P.h"

ASala2P::ASala2P(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NumeroPortas = ENumeroPortas::DUAS;
	DirecaoSala = EFormatoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::LESTE);
	bVisitada = false;
}


