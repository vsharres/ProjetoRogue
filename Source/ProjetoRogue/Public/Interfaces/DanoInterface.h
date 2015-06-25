// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DanoInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UDanoInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IDanoInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void ReceberDano(const float& dano);

	virtual void AplicarStatsProjetil(class AProjectil* projetil);
};
