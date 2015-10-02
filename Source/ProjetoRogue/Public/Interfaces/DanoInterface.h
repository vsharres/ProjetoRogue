// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DanoInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UDanoInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IDanoInterface
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Receber Dano", Keywords = "Receber Dano"), Category = "DanoInterface")
		virtual void ReceberDano(const float& dano, class AProjectil* projetil);

	virtual void AplicarStatsProjetil(AProjectil* projetil);
};
