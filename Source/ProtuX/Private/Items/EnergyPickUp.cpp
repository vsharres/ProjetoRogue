// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnergyPickUp.h"

AEnergyPickUp::AEnergyPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	IncEnergy = 10;
	Type = EPickUpType::ENERGY;

	//Assigning trigger delegates
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AEnergyPickUp::OutlineEndOverlap);
	
}

void AEnergyPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //check if the overlap was caused by the player
	{
		//adding energy to the player and destroy the pickup
		player->AddEnergy(IncEnergy);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}
	
}

void AEnergyPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(true); //active outline effect
	}
}

void AEnergyPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(false); //deactivate the outline effect
	}
}

