// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpVida.h"
#include "Jogador.h"

APickUpVida::APickUpVida(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IncVida = 25;
	Tipo = ETipoPickUp::VIDA;
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpVida::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpVida::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpVida::OutlineEndOverlap);
	
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

void APickUpVida::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void APickUpVida::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void APickUpVida::BeginPlay()
{	
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Super::BeginPlay();
}
