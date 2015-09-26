// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpVida.h"
#include "Jogador.h"

APickUpVida::APickUpVida(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncVida = 25;
	Tipo = ETipoPickUp::VIDA;
	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpVida::ColisorOverlap);
}

void APickUpVida::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherActor != this && OtherComp)
	{
		jogador->AdicionarVida(IncVida);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}

	
}
