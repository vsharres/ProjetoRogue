// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ItemProjetil.generated.h"

/**
 *
 */
UCLASS()
class PROJETOROGUE_API UItemProjetil : public UItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

	UItemProjetil();	

	//INTERFACES
	virtual void AplicarItem_Implementation() override;

	virtual void RemoverItem_Implementation() override;

};
