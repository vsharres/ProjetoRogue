// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "PickUp.h"


APickUp::APickUp(const FObjectInitializer& ObjectInitializer)
{
 	//Inicializando as propriedades e criando os componenetes
	PrimaryActorTick.bCanEverTick = false;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;
	
	TriggerCatch = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("TriggerCatch"));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerCatch->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerCatch->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerCatch->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerCatch->SetSphereRadius(50.0f);
	TriggerCatch->AttachToComponent(Mesh, Rules);

	TriggerOutline = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("TriggerOutline"));
	TriggerOutline->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerOutline->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerOutline->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerOutline->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerOutline->SetSphereRadius(100.0f);
	TriggerOutline->AttachToComponent(Mesh, Rules);

	IncHealth = 0.0f;
	IncEnergy = 0;
	IncScraps = 0;
	ExplosionDelta = 50.0f;
	ExplosionForce = 500.0f;
}

USphereComponent* APickUp::GetCollider()
{
	return TriggerCatch;
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

	//Direcao da for�a de spawn do pickup usando um vetor randomico
	FVector direction = FVector(random.FRandRange(GetActorLocation().X - ExplosionDelta, GetActorLocation().X + ExplosionDelta),
		random.FRandRange(GetActorLocation().Y - ExplosionDelta, GetActorLocation().Y + ExplosionDelta),
		GetActorLocation().Z + ExplosionDelta * 2.0f);

	//Impulsionar o pick up
	Mesh->AddImpulse(direction.GetSafeNormal() * ExplosionForce);
	
}

