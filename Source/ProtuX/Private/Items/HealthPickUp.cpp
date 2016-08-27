// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "HealthPickUp.h"

AHealthPickUp::AHealthPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	IncHealth = 25;
	Type = EPickUpType::HEALTH;

	//Assigning trigger delegates
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AHealthPickUp::OutlineEndOverlap);
	
}

void AHealthPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //check if the overlap was caused by the player
	{
		//adding health to the player and destroy the pickup
		player->AddHealth(IncHealth);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}

}

void AHealthPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(true); //active outline effect
	}
}

void AHealthPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(false); //deactivate the outline effect
	}
}
