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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void AtivarItem();
		virtual void AtivarItem_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DesativarItem();
		virtual void DesativarItem_Implementation();

	virtual void AplicarItem_Implementation() override;

	virtual void RemoverItem_Implementation() override;
	
	
	
	
};
