// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "HealthPickUp.h"

AHealthPickUp::AHealthPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	IncHealth = 25;
	Type = EPickUpType::HEALTH;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AHealthPickUp::OutlineEndOverlap);
	
}

void AHealthPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherActor != this && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		//Adicionar vida ao jogador.
		player->AddHealth(IncHealth);
		player->GeneratePickUpPopUp(this);
		Destroy();
	}

}

void AHealthPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void AHealthPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) // checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}
