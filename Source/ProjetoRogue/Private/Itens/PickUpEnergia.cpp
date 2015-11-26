// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "PickUpEnergia.h"
#include "Jogador.h"

APickUpEnergia::APickUpEnergia(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	IncEnergia = 10;
	Tipo = ETipoPickUp::ENERGIA;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpEnergia::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpEnergia::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpEnergia::OutlineEndOverlap);
	
}

void APickUpEnergia::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherActor != this && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		//Adicionar energia ao jogador
		jogador->AdicionarEnerngia(IncEnergia);
		jogador->GerarPickUpPopUp(this);
		Destroy();
	}
	
}

void APickUpEnergia::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void APickUpEnergia::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}

