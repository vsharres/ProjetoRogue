// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Corredor.h"


// Sets default values
ACorredor::ACorredor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanBeDamaged = false;

	OffsetCorredor = 3000.0f;
	EscalaPadrao = FVector(5.0f, 5.0f, 5.0f);

}

FVector ACorredor::GetEscala()
{
	return EscalaPadrao;
}

int32 ACorredor::GetOffset()
{
	return OffsetCorredor;
}

