// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala.h"


// Sets default values
ASala::ASala()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumeroPortas = ENumeroPortas::UMA;
	DirecaoSala = EDirecaoSala::PADRAO;
	TipoSala = ETipoSala::NORMAL;
	SalasConectadas.Empty();
	DirecaoPortas.Add(EDirecaoPortas::OESTE);
	bVisitada = false;

	OffsetSala = 4640.0f;
	EscalaPadrao = FVector(5.0f, 5.0f, 5.0f);

}

FVector ASala::GetEscala()
{
	return EscalaPadrao;
}

int32 ASala::GetOffset()
{
	return OffsetSala;
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

TArray<TEnumAsByte<EDirecaoPortas>> ASala::GetArrayPortas()
{
	return DirecaoPortas;
}

