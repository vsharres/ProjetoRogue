// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Corredor.h"


// Sets default values
ACorredor::ACorredor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanBeDamaged = false;

	OffsetCorredor = 2320.0f;
	EscalaPadrao = FVector(12.0f, 12.0f, 12.0f);

}

FVector ACorredor::GetEscala()
{
	return EscalaPadrao;
}

int32 ACorredor::GetOffset()
{
	return OffsetCorredor;
}

