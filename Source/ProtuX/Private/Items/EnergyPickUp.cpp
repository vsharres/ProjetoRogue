// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnergyPickUp.h"

AEnergyPickUp::AEnergyPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	IncEnergy = 10;
	Type = EPickUpType::ENERGY;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AEnergyPickUp::OutlineEndOverlap);
	
}

void AEnergyPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		//Adicionar energia ao jogador
		player->AddEnergy(IncEnergy);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}
	
}

void AEnergyPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void AEnergyPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}

