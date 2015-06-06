// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itens/Item.h"
#include "ItemAtivo.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API UItemAtivo : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bAtivo;

	UItemAtivo();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void AtivarItem();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DesativarItem();

	virtual void AplicarItem() override;

	virtual void RemoverItem() override;
	
	
	
	
};
