// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/Item.h"
#include "ItemPassivo.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AItemPassivo : public AItem
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY()
		FItemStats Stats;

	AItemPassivo();
	
};
