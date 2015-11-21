// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Projectil.h"

AProjectil::AProjectil(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;
	bAtivo = false;
	
	//Criando o componente de colisao e inicializando suas propriedades.
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
	Mesh->AttachTo(RootComponent); //Mesh do projétil é o root do ator.
	
	//Criando o componente de movimentação, que é responsável pela comportamento de movimentação do ator.
	CompMovimentacao = ObjectInitializer.CreateAbstractDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompMovimentacao"));
	CompMovimentacao->UpdatedComponent = CompCollisao;
	CompMovimentacao->InitialSpeed = 0.0f;
	CompMovimentacao->MaxSpeed = 4000.0f;
	CompMovimentacao->bRotationFollowsVelocity = true;
	CompMovimentacao->ProjectileGravityScale = 0.f;
	CompMovimentacao->bAutoActivate = false;

	//Inicializando os stats.
	Stats = FProjetilStats();
	
	//Inicializando os efeitos.
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

	(Cast<IDanoInterface>(Inicializador))->AplicarStatsProjetil(this); //Inicializando o projetil com o ator que vai ser responsável por "atirar" o projétil.
	
	if (!CompMovimentacao->UpdatedComponent) //Set do componente a ser atualizado com o componente de movimentação.
	{
		CompMovimentacao->SetUpdatedComponent(this->RootComponent);
		
	}
	
	//Velocidade do projetil é somado a velocidade do personagem
	CompMovimentacao->SetVelocityInLocalSpace(FVector(1, 0, 0) * Stats.Velocidade + Inicializador->GetCharacterMovement()->Velocity.ForwardVector);

}

void AProjectil::AtivarProjetil(const FVector& Location, const FRotator& Rotator, ACharacter* Inicializador)
{
	bAtivo = true; //Projetil está ativado
	
	//Colocar o projétil na posição inicial, e rotacionado na direção que foi mirado. 
	SetActorLocation(Location);
	SetActorRotation(Rotator);
	Instigator = Inicializador;

	SetActorHiddenInGame(false); //Mostrar o projetil

	InicializarProjetil(Inicializador); //Inicializar o projétil e começar a se mover.
	CompCollisao->Activate(true);
	CompMovimentacao->Activate(true);	

}

void AProjectil::DesativarProjetil()
{ 
	bAtivo = false; //Projétil está desativado.

	SetActorHiddenInGame(true); //Esconder projétil

	SetActorLocation(FVector(0, 1000, 3000)); //Colocar numa posição fora do jogo
	
	//Desativar colisao e a movimentação
	CompCollisao->Deactivate();
	CompMovimentacao->Deactivate();
	
}

void AProjectil::GerarEfeitosImpacto(const FHitResult& Hit)
{
	FRandomStream Stream; //Stream randomico para determinar a rotacao do efeito de impacto

	FRotator rotTemp = Hit.ImpactNormal.Rotation();

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //Rotacao do efeito

	//Spawn do efeito de impacto
	UGameplayStatics::SpawnEmitterAtLocation(this, ImapctoEfeitos.Efeito, Hit.ImpactPoint, rotTemp, true);

	//UGameplayStatics::PlaySoundAtLocation(this, SomImpacto, Hit.ImpactPoint);

	//Spawn do decal na posicao de impacto doo tiro.
	UGameplayStatics::SpawnDecalAttached(ImapctoEfeitos.DecalMaterial, FVector(ImapctoEfeitos.DecalTamanho, ImapctoEfeitos.DecalTamanho, 1.0F), Hit.GetComponent(), Hit.BoneName, Hit.ImpactPoint, rotTemp, EAttachLocation::KeepWorldPosition, ImapctoEfeitos.DecalVida);

}

void AProjectil::GerarEfeitosTiro(const FVector& Location, const FRotator& Rotator, USceneComponent* Componente, FName Nome)
{
	FRandomStream Stream; //Stream randomico para a rotacao do efeito de tiro

	FRotator rotTemp = Rotator;

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //Rotacao do efeito

	UGameplayStatics::SpawnSoundAttached(TiroEfeitos.SomTiro, Componente, Nome);
	//Spawn do efeito de tiro.
	UGameplayStatics::SpawnEmitterAttached(TiroEfeitos.TiroFlash, Componente, Nome);
}

// Called when the game starts or when spawned
void AProjectil::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização.

}

// Called every frame
void AProjectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Interface de Tick

}

void AProjectil::OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDanoInterface* danoInterface = Cast<IDanoInterface>(Hit.GetActor()); //Checar que o ator que foi atingido com o projétil pode receber dano.

	if (danoInterface && Hit.GetActor() != this->Instigator) //Checar validade dos ponteiros e que o ator atingido nao foi o ator que atirou o projetil
	{
		danoInterface->ReceberDano(this->Stats.Dano, this, Hit); //Receber o dano do projetil
		DesativarProjetil();
		GerarEfeitosImpacto(Hit);
		Atingiu();	//Evento para o blueprint
	}
	else if (Hit.GetActor() != this->Instigator) //Caso o ator nao seja um ator que receba dano, apenas desativar o projetil.
	{
		DesativarProjetil();
		GerarEfeitosImpacto(Hit);
		Atingiu();
	}
}



