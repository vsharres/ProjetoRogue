// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpEnergia.h"
#include "Jogador.h"

APickUpEnergia::APickUpEnergia(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncEnergia = 10;
	Tipo = ETipoPickUp::ENERGIA;
	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpEnergia::ColisorOverlap);
}

void APickUpEnergia::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast())
	{
		jogador->AdicionarEnerngia(IncEnergia);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}

	
}
