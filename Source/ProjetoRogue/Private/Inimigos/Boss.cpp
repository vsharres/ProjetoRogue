// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Boss.h"


ABoss::ABoss(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TipoInimigo = ETipoInimigo::BOSS;

}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
