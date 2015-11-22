// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemSpawner.h"

AItemSpawner::AItemSpawner(const FObjectInitializer& ObjectInitializer)
{
 	//Inicilizando as propriedades
	PrimaryActorTick.bCanEverTick = true;

	Colisor = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("Colisor"));
	Colisor->SetCapsuleHalfHeight(32.0f);
	Colisor->SetCapsuleRadius(15.0f);
	RootComponent = Colisor;

}

