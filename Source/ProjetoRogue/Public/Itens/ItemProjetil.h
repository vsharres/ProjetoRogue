// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/Item.h"
#include "ItemProjetil.generated.h"

/**
 *
 */
UCLASS()
class PROJETOROGUE_API UItemProjetil : public UItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

	UItemProjetil();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Atirar Projetil", Keywords = "Atirar Projetil"), Category = "Item")
		void Atirar();
		virtual void Atirar_Implementation();

	//INTERFACES
	virtual void AplicarItem_Implementation() override;

	virtual void RemoverItem_Implementation() override;
};
