// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpEnergia.h"
#include "Jogador.h"

APickUpEnergia::APickUpEnergia(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncEnergia = 10;
	Tipo = ETipoPickUp::ENERGIA;
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpEnergia::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpEnergia::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpEnergia::OutlineEndOverlap);
	
}

void APickUpEnergia::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherActor != this && OtherComp)
	{
		jogador->AdicionarEnerngia(IncEnergia);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}
	
}

void APickUpEnergia::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void APickUpEnergia::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void APickUpEnergia::BeginPlay()
{
	
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Super::BeginPlay();
}
