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

	TriggerCatch = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("TriggerCatch"));
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerCatch->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerCatch->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerCatch->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerCatch->SetSphereRadius(40.0f);
	TriggerCatch->AttachTo(Mesh);

	TriggerOutline = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("TriggerOutline"));
	TriggerOutline->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerOutline->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerOutline->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerOutline->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerOutline->SetSphereRadius(100.0f);
	TriggerOutline->AttachTo(Mesh);

	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUp::OutlineEndOverlap);

	IncVida = 0.0f;
	IncEnergia = 0;
	IncMoedas = 0;
	ExplosaoDelta = 50.0f;
	ExplosaoForca = 500.0f;
}

USphereComponent* APickUp::GetColisor()
{
	return TriggerCatch;
}

UStaticMeshComponent* APickUp::GetMesh()
{
	return Mesh;
}

void APickUp::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void APickUp::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(false);
	}
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


