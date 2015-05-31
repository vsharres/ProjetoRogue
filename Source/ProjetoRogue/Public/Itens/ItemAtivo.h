// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/Item.h"
#include "ItemAtivo.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AItemAtivo : public AItem
{
	GENERATED_BODY()

	
public:

	UPROPERTY()
		bool bAtivo;

	UPROPERTY()
		float Cooldown;

	UPROPERTY()
		FItemStats Stats;

	AItemAtivo();
	
	
};
