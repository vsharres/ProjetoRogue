// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Projeteis/Projectil.h"


// Sets default values
AProjectil::AProjectil(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;

	CompCollisao = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ColisaoEsfera"));
	CompCollisao->InitSphereRadius(52.0f);
	CompCollisao->SetWorldScale3D(FVector(0.5f));
	CompCollisao->bTraceComplexOnMove = true;
	CompCollisao->SetCollisionObjectType(ECC_WorldDynamic);
	CompCollisao->SetCollisionResponseToAllChannels(ECR_Ignore);
	CompCollisao->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CompCollisao->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CompCollisao->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CompCollisao->OnComponentHit.AddDynamic(this, &AProjectil::OnHit);
	RootComponent = CompCollisao;

	Mesh = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	CompMovimentacao = ObjectInitializer.CreateAbstractDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompMovimentacao"));
	CompMovimentacao->UpdatedComponent = CompCollisao;
	CompMovimentacao->InitialSpeed = 2000.0f;
	CompMovimentacao->MaxSpeed = 4000.0f;
	CompMovimentacao->bRotationFollowsVelocity = true;
	CompMovimentacao->ProjectileGravityScale = 0.f;

	Stats = FProjetilStats();

}

// Called when the game starts or when spawned
void AProjectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectil::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectil::OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDanoInterface* danoInterface = Cast<IDanoInterface>(Hit.GetActor());

	if (danoInterface)
	{
		danoInterface->ReceberDano(this->Stats.Dano);
	}

	Destroy();
}

UProjectileMovementComponent* AProjectil::GetMovProjetil()
{
	return CompMovimentacao;
}

