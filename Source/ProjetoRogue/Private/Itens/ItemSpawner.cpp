// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "ItemSpawner.h"


// Sets default values
AItemSpawner::AItemSpawner(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colisor = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("Colisor"));
	Colisor->SetCapsuleHalfHeight(32.0f);
	Colisor->SetCapsuleRadius(15.0f);
	RootComponent = Colisor;

	Sprite = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("Sprite"));
	Sprite->SetVisibility(true);
	Sprite->AttachTo(RootComponent);

}

