// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DanoInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UDanoInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IDanoInterface
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Receber Dano", Keywords = "Receber Dano"), Category = "DanoInterface")
	virtual void ReceberDano(const float& dano);

	virtual void AplicarStatsProjetil(class AProjectil* projetil);
};
