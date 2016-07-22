// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Projectile.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;
	bIsActive = false;
	
	//Criando o componente de colisao e inicializando suas propriedades.
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ColisaoEsfera"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->bTraceComplexOnMove = true;
	CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	CollisionComp->bAutoActivate = false;
	CollisionComp->bAutoRegister = true;
	RootComponent = CollisionComp;

	Mesh = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	Mesh->AttachToComponent(RootComponent, Rules); //Mesh do proj�til � o root do ator.
	
	//Criando o componente de movimenta��o, que � respons�vel pela comportamento de movimenta��o do ator.
	MovementComp = ObjectInitializer.CreateAbstractDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompMovimentacao"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->InitialSpeed = 0.0f;
	MovementComp->MaxSpeed = 4000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bAutoActivate = false;

	//Inicializando os stats.
	Stats = FProjectileStats();
	
	//Inicializando os efeitos.
	ImpactFX = FProjectileImpactEffect();

}

UStaticMeshComponent* AProjectile::GetProjectileMesh()
{
	return Mesh;
}

UProjectileMovementComponent* AProjectile::GetMovComp()
{
	return MovementComp;
}

void AProjectile::InitializeProjectile(ACharacter* initializer)
{

	(Cast<IDamageInterface>(initializer))->ApplyProjectileStats(this); //Inicializando o projetil com o ator que vai ser respons�vel por "atirar" o proj�til.
	
	if (!MovementComp->UpdatedComponent) //Set do componente a ser atualizado com o componente de movimenta��o.
	{
		MovementComp->SetUpdatedComponent(this->RootComponent);
		
	}
	
	//Velocidade do projetil � somado a velocidade do personagem
	MovementComp->SetVelocityInLocalSpace(FVector(1, 0, 0) * Stats.Speed + initializer->GetCharacterMovement()->Velocity.ForwardVector);

}

void AProjectile::ActivateProjectile(const FVector& location, const FRotator& rotator, ACharacter* initializer)
{
	bIsActive = true; //Projetil est� ativado
	
	//Colocar o proj�til na posi��o inicial, e rotacionado na dire��o que foi mirado. 
	SetActorLocation(location);
	SetActorRotation(rotator);
	Instigator = initializer;

	SetActorHiddenInGame(false); //Mostrar o projetil

	InitializeProjectile(initializer); //Inicializar o proj�til e come�ar a se mover.
	CollisionComp->Activate(true);
	MovementComp->Activate(true);	

}

void AProjectile::DeactivateProjectile()
{ 
	bIsActive = false; //Proj�til est� desativado.

	SetActorHiddenInGame(true); //Esconder proj�til

	SetActorLocation(FVector(0, 1000, 3000)); //Colocar numa posi��o fora do jogo
	
	//Desativar colisao e a movimenta��o
	CollisionComp->Deactivate();
	MovementComp->Deactivate();
	
}

void AProjectile::SpawnImpactFX(const FHitResult& Hit)
{
	FRandomStream Stream; //Stream randomico para determinar a rotacao do efeito de impacto

	FRotator rotTemp = Hit.ImpactNormal.Rotation();

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //Rotacao do efeito

	//Spawn do efeito de impacto
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX.Effect, Hit.ImpactPoint, rotTemp, true);

	//Spawn do decal na posicao de impacto doo tiro.
	UGameplayStatics::SpawnDecalAttached(ImpactFX.DecalMaterial, FVector(ImpactFX.DecalSize, ImpactFX.DecalSize, 1.0F), Hit.GetComponent(), Hit.BoneName, Hit.ImpactPoint, rotTemp, EAttachLocation::KeepWorldPosition, ImpactFX.DecalHealth);

}

void AProjectile::SpawnShootFX(const FVector& location, const FRotator& rotator, USceneComponent* component, FName name)
{
	FRandomStream Stream; //Stream randomico para a rotacao do efeito de tiro

	FRotator rotTemp = rotator;

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //Rotacao do efeito

	UGameplayStatics::SpawnSoundAttached(ShootFX.ShootSound, component, name);
	//Spawn do efeito de tiro.
	UGameplayStatics::SpawnEmitterAttached(ShootFX.ShootFlash, component, name);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicializa��o.

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Interface de Tick

}

void AProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDamageInterface* damageInterface = Cast<IDamageInterface>(Hit.GetActor()); //Checar que o ator que foi atingido com o proj�til pode receber dano.

	if (damageInterface && Hit.GetActor() != this->Instigator) //Checar validade dos ponteiros e que o ator atingido nao foi o ator que atirou o projetil
	{
		damageInterface->ReceiveDamage(this->Stats.Damage, this, Hit); //Receber o dano do projetil
		DeactivateProjectile();
		SpawnImpactFX(Hit);
		OnHitTarget();	//Evento para o blueprint
	}
	else if (Hit.GetActor() != this->Instigator) //Caso o ator nao seja um ator que receba dano, apenas desativar o projetil.
	{
		DeactivateProjectile();
		SpawnImpactFX(Hit);
		OnHitTarget();
	}
}



