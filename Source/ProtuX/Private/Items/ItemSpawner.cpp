// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ItemSpawner.h"

AItemSpawner::AItemSpawner(const FObjectInitializer& ObjectInitializer)
{
 	//Inicilizando as propriedades
	PrimaryActorTick.bCanEverTick = true;

	Collider = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("Colisor"));
	Collider->SetCapsuleHalfHeight(32.0f);
	Collider->SetCapsuleRadius(15.0f);
	RootComponent = Collider;

}

