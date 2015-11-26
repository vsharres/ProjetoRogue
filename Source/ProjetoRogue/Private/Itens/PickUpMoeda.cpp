// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpMoeda.h"
#include "Jogador.h"


APickUpMoeda::APickUpMoeda(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	IncScraps = 2;
	Tipo = ETipoPickUp::SCRAP;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpMoeda::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpMoeda::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpMoeda::OutlineEndOverlap);
	
}

void APickUpMoeda::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherActor != this && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		//Adicionar scrap ao jogador.
		jogador->AdicionarMoedas(IncScraps);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}

	
}

void APickUpMoeda::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void APickUpMoeda::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}
