// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Projectil.h"


// Sets default values
AProjectil::AProjectil(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;
	bAtivo = false;

	CompCollisao = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ColisaoEsfera"));
	CompCollisao->InitSphereRadius(10.0f);
	CompCollisao->bTraceComplexOnMove = true;
	CompCollisao->SetCollisionObjectType(ECC_WorldDynamic);
	CompCollisao->SetCollisionResponseToAllChannels(ECR_Ignore);
	CompCollisao->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CompCollisao->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CompCollisao->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CompCollisao->OnComponentHit.AddDynamic(this, &AProjectil::OnHit);
	CompCollisao->bAutoActivate = false;
	CompCollisao->bAutoRegister = true;
	RootComponent = CompCollisao;

	Mesh = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	CompMovimentacao = ObjectInitializer.CreateAbstractDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompMovimentacao"));
	CompMovimentacao->UpdatedComponent = CompCollisao;
	CompMovimentacao->InitialSpeed = 0.0f;
	CompMovimentacao->MaxSpeed = 4000.0f;
	CompMovimentacao->bRotationFollowsVelocity = true;
	CompMovimentacao->ProjectileGravityScale = 0.f;
	CompMovimentacao->bAutoActivate = false;

	Stats = FProjetilStats();

	ImapctoEfeitos = FProjetilImpactoEfeito();

}

UStaticMeshComponent* AProjectil::GetProjetilMesh()
{
	return Mesh;
}

UProjectileMovementComponent* AProjectil::GetMovProjetil()
{
	return CompMovimentacao;
}

void AProjectil::InicializarProjetil(ACharacter* Inicializador)
{

	(Cast<IDanoInterface>(Inicializador))->AplicarStatsProjetil(this);
	
	if (!CompMovimentacao->UpdatedComponent)
	{
		CompMovimentacao->SetUpdatedComponent(this->RootComponent);
		
	}
	
	CompMovimentacao->SetVelocityInLocalSpace(FVector(1, 0, 0) * Stats.Velocidade + Inicializador->GetCharacterMovement()->Velocity.ForwardVector);

}

void AProjectil::AtivarProjetil(const FVector& Location, const FRotator& Rotator, ACharacter* Inicializador)
{
	bAtivo = true;

	SetActorLocation(Location);
	SetActorRotation(Rotator);
	Instigator = Inicializador;

	SetActorHiddenInGame(false);

	InicializarProjetil(Inicializador);
	CompCollisao->Activate(true);
	CompMovimentacao->Activate(true);	

}

void AProjectil::DesativarProjetil()
{
	bAtivo = false;

	SetActorHiddenInGame(true);

	SetActorLocation(FVector(0, 0, 3000));

	CompCollisao->Deactivate();
	CompMovimentacao->Deactivate();
	
}

void AProjectil::GerarEfeitosImpacto(const FHitResult& Hit)
{
	FRandomStream Stream;

	FRotator rotTemp = Hit.ImpactNormal.Rotation();

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180));

	UGameplayStatics::SpawnEmitterAtLocation(this, ImapctoEfeitos.Efeito, Hit.ImpactPoint, rotTemp, true);

	//UGameplayStatics::PlaySoundAtLocation(this, SomImpacto, Hit.ImpactPoint);

	UGameplayStatics::SpawnDecalAttached(ImapctoEfeitos.DecalMaterial, FVector(ImapctoEfeitos.DecalTamanho, ImapctoEfeitos.DecalTamanho, 1.0F), Hit.GetComponent(), Hit.BoneName, Hit.ImpactPoint, rotTemp, EAttachLocation::KeepWorldPosition, ImapctoEfeitos.DecalVida);

}

void AProjectil::GerarEfeitosTiro(const FVector& Location, const FRotator& Rotator, USceneComponent* Componente, FName Nome)
{
	FRandomStream Stream;

	FRotator rotTemp = Rotator;

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180));

	UGameplayStatics::SpawnEmitterAttached(TiroEfeitos.TiroFlash, Componente, Nome);
}

// Called when the game starts or when spawned
void AProjectil::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectil::OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDanoInterface* danoInterface = Cast<IDanoInterface>(Hit.GetActor());

	if (danoInterface && Hit.GetActor() != this->Instigator)
	{
		danoInterface->ReceberDano(this->Stats.Dano, this, Hit);
		DesativarProjetil();
		GerarEfeitosImpacto(Hit);
		Atingiu();		
	}
	else if (Hit.GetActor() != this->Instigator)
	{
		DesativarProjetil();
		GerarEfeitosImpacto(Hit);
		Atingiu();
	}
}



