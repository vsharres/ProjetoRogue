// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "PickUpVida.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API APickUpVida : public APickUp
{
	GENERATED_BODY()

		APickUpVida(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION()
		void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
