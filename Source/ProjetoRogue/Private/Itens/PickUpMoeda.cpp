// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpMoeda.h"
#include "Jogador.h"


APickUpMoeda::APickUpMoeda(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncMoedas = 2;
	Tipo = ETipoPickUp::MOEDA;
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpMoeda::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpMoeda::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpMoeda::OutlineEndOverlap);
	
}

void APickUpMoeda::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherActor != this && OtherComp)
	{
		jogador->AdicionarMoedas(IncMoedas);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}

	
}

void APickUpMoeda::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void APickUpMoeda::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void APickUpMoeda::BeginPlay()
{	
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Super::BeginPlay();
}
