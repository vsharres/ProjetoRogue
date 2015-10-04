// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUp.h"

// Sets default values
APickUp::APickUp(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	Colisor = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("Colisor"));
	Colisor->AttachTo(Mesh);

	IncVida = 0.0f;
	IncEnergia = 0;
	IncMoedas = 0;
	ExplosaoDelta = 50.0f;
	ExplosaoForca = 500.0f;
}

UCapsuleComponent* APickUp::GetColisor()
{
	return Colisor;
}

UStaticMeshComponent* APickUp::GetMesh()
{
	return Mesh;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();

	FRandomStream random;

	random.GenerateNewSeed();

	FVector direcao = FVector(random.FRandRange(GetActorLocation().X - ExplosaoDelta, GetActorLocation().X + ExplosaoDelta),
		random.FRandRange(GetActorLocation().Y - ExplosaoDelta, GetActorLocation().Y + ExplosaoDelta),
		GetActorLocation().Z + ExplosaoDelta * 2.0f);

	Mesh->AddImpulse(direcao.GetSafeNormal() * ExplosaoForca);
	
}


