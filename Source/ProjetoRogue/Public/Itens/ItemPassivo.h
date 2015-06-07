// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/Item.h"
#include "ItemPassivo.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API UItemPassivo : public UItem
{
	GENERATED_BODY()

public:

	UItemPassivo();

	virtual void AplicarItem_Implementation() override;

	virtual void RemoverItem_Implementation() override;
	
	
	
	
};
