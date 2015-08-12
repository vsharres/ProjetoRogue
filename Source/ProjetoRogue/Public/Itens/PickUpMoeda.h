// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/PickUp.h"
#include "PickUpMoeda.generated.h"

/**
 *
 */
UCLASS()
class PROJETOROGUE_API APickUpMoeda : public APickUp
{
	GENERATED_BODY()

		APickUpMoeda(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
