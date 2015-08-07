// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala3P.h"


ASala3P::ASala3P()
{
	NumeroPortas = ENumeroPortas::TRES;
	DirecaoSala = EFormatoSala::PADRAO;
	SalasConectadas.Empty();
	DirecaoPortas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	DirecaoPortas.Add(EDirecaoPorta::SUL);
	DirecaoPortas.Add(EDirecaoPorta::NORTE);
	bVisitada = false;
}

