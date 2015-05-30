// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala.h"


// Sets default values
ASala::ASala()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumeroPortas = ENumeroPortas::UMA;
	DirecaoSala = EDirecaoSala::NORMAL;
	TipoSala = ETipoSala::NORMAL;
	SalasConectadas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	bVisitada = false;

}

ENumeroPortas ASala::GetNumPortas()
{
	return NumeroPortas;
}

EDirecaoSala ASala::GetDirecao()
{
	return DirecaoSala;
}

ETipoSala ASala::GetTipo()
{
	return TipoSala;
}

TArray<TEnumAsByte<EDirecaoPortas>> ASala::GetDirecaoPortas()
{
	return DirecaoPortas;
}

