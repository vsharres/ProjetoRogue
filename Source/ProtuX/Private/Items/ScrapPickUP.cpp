// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ScrapPickUP.h"


AScrapPickUP::AScrapPickUP(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	IncScraps = 2;
	Type = EPickUpType::SCRAP;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AScrapPickUP::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AScrapPickUP::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AScrapPickUP::OutlineEndOverlap);
	
}

void AScrapPickUP::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		//Adicionar scrap ao jogador.
		player->AddCoins(IncScraps);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}

	
}

void AScrapPickUP::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void AScrapPickUP::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}
