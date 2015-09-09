// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUp.h"

// Sets default values
APickUp::APickUp(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Colisor = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("Colisor"));
	RootComponent = Colisor;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->AttachTo(Colisor);

	IncVida = 0.0f;
	IncEnergia = 0;
	IncMoedas = 0;
}

UCapsuleComponent* APickUp::GetColisor()
{
	return Colisor;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}


