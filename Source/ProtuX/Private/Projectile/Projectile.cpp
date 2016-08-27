// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Projectile.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
{
	//Initializing properties
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = false;
	bIsActive = false;
	Stats = FProjectileStats();
	ImpactFX = FProjectileImpactEffect();
	
	//initializing collision component and its properties
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
	Mesh->AttachToComponent(RootComponent, Rules); 
	
	//initializing the movement component, which is responsible for moving the projectile
	MovementComp = ObjectInitializer.CreateAbstractDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompMovimentacao"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->InitialSpeed = 0.0f;
	MovementComp->MaxSpeed = 4000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bAutoActivate = false;

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
	//initializing the projectile with the actor that sill cause the damage
	(Cast<IDamageInterface>(initializer))->ApplyProjectileStats(this);
	
	if (!MovementComp->UpdatedComponent) //set the movement component of the projectile to active, so that the projectile starts moving
	{
		MovementComp->SetUpdatedComponent(this->RootComponent);
		
	}
	
	//projectile speed is added to the actor's speed
	MovementComp->SetVelocityInLocalSpace(FVector(1, 0, 0) * Stats.Speed + initializer->GetCharacterMovement()->Velocity.ForwardVector);

}

void AProjectile::ActivateProjectile(const FVector& location, const FRotator& rotator, ACharacter* initializer)
{
	bIsActive = true;
	
	//set the projectile at the start position, and rotates to the aim rotation
	SetActorLocation(location);
	SetActorRotation(rotator);
	Instigator = initializer;

	SetActorHiddenInGame(false);

	InitializeProjectile(initializer);
	CollisionComp->Activate(true);
	MovementComp->Activate(true);	

}

void AProjectile::DeactivateProjectile()
{ 
	bIsActive = false;
	SetActorHiddenInGame(true);

	//set the projectile in a hidden position outside game
	SetActorLocation(FVector(0, 1000, 3000)); 
	
	//deactive collisions and movement
	CollisionComp->Deactivate();
	MovementComp->Deactivate();
	
}

void AProjectile::SpawnImpactFX(const FHitResult& Hit)
{
	FRandomStream Stream; //random stream

	FRotator rotTemp = Hit.ImpactNormal.Rotation();

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //randomly rotate the effect

	//impact effects sound spawn
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX.Effect, Hit.ImpactPoint, rotTemp, true);

	//spawn decal effect on impact position
	UGameplayStatics::SpawnDecalAttached(ImpactFX.DecalMaterial, 
		FVector(ImpactFX.DecalSize, ImpactFX.DecalSize, 1.0F), 
		Hit.GetComponent(), 
		Hit.BoneName, 
		Hit.ImpactPoint, 
		rotTemp, 
		EAttachLocation::KeepWorldPosition, ImpactFX.DecalHealth);

}

void AProjectile::SpawnShootFX(const FVector& location, const FRotator& rotator, USceneComponent* component, FName name)
{
	FRandomStream Stream; //random stream

	FRotator rotTemp = rotator;

	rotTemp = FRotator(rotTemp.Pitch, rotTemp.Yaw, Stream.FRandRange(-180, 180)); //randomly rotate the effect

	//spawn shooting sound FX
	UGameplayStatics::SpawnSoundAttached(ShootFX.ShootSound, component, name);

	//Spawn shooting particle effect
	UGameplayStatics::SpawnEmitterAttached(ShootFX.ShootFlash, component, name);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização.

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Interface de Tick

}

void AProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDamageInterface* damageInterface = Cast<IDamageInterface>(Hit.GetActor()); //check that the actor that has hit can receive damage

	if (damageInterface && Hit.GetActor() != this->Instigator) //Check validity of the actor's pointer
	{
		damageInterface->ReceiveDamage(this->Stats.Damage, this, Hit); //receive damage
		DeactivateProjectile();
		SpawnImpactFX(Hit);
		OnHitTarget();	//trigger blueprint event
	}
	else if (Hit.GetActor() != this->Instigator) //if the actor hit can't receive damage, deactivate the projectile (like when hitting walls)
	{
		DeactivateProjectile();
		SpawnImpactFX(Hit);
		OnHitTarget();
	}
}



