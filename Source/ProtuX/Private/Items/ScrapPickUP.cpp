// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ScrapPickUP.h"


AScrapPickUP::AScrapPickUP(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	IncScraps = 2;
	Type = EPickUpType::SCRAP;

	//Assigning trigger delegates
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AScrapPickUP::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AScrapPickUP::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AScrapPickUP::OutlineEndOverlap);
	
}

void AScrapPickUP::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //check if the overlap was caused by the player
	{
		//Adding scrap to the player
		player->AddCoins(IncScraps);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}
	
}

void AScrapPickUP::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(true); //activate outline effect
	}
}

void AScrapPickUP::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(false); //deactivate outline effect
	}
}
