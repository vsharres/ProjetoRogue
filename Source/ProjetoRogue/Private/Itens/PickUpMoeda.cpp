// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpMoeda.h"
#include "Public/Jogador/Jogador.h"


APickUpMoeda::APickUpMoeda(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncMoedas = 1;
	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpMoeda::ColisorOverlap);
}

void APickUpMoeda::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast())
	{
		jogador->AdicionarMoedas(IncMoedas);
		Destroy();
	}

	
}