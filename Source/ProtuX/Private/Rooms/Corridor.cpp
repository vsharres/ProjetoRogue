// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Corridor.h"


// Sets default values
ACorridor::ACorridor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	//Inicializando as propriedades
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;

	OffsetCorridor = 3000.0f;
	StandardScale = FVector(5.0f, 5.0f, 5.0f);

}

FVector ACorridor::GetScale()
{
	return StandardScale;
}

float ACorridor::GetOffset()
{
	return OffsetCorridor;
}

