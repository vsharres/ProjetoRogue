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

	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bAtivo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		bool bProjetilPadrao;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Energia")
		float EnergiaUtilizada;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

	UItemProjetil();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void AtivarItem();
	virtual void AtivarItem_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DesativarItem();
	virtual void DesativarItem_Implementation();

	//INTERFACES
	virtual void AplicarItem_Implementation() override;

	virtual void RemoverItem_Implementation() override;

};
