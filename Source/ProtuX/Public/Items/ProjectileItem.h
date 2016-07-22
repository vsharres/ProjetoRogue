// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ProjectileItem.generated.h"

/*
* Classe derivada da classe UItem
* Classe que representa um item projetil, que representa o item respons�vel pelo tiro do jogador. Items de projeteis s�o ativados pelo jogador explicitamente.
*/
UCLASS()
class PROTUX_API UProjectileItem : public UItem
{
	GENERATED_BODY()

#pragma region Properties
public:

	/* Propriedade indicando se o item est� ativo. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bIsActive;

	/* Propriedade indicando se este item proj�til � o item padr�o(item com qual o jogador come�a). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		bool bIsStandardProjectile;

	/* Propriedade que indica a quantidade de energia utilizado pelo item por deltatime. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float EnergyRequired;

	/* Classe do projetil a ser gerado quando o item � ativado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<class AProjectile> Projectile;

	/* Mesh do detalhe do dano. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* CannonDamageMesh;

	/* Instancia do material do detalhe do dano. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* CannonDamageMaterial;

	/* Mesh do detalhe de precis�o. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* CannonAccuracyMesh;

	/*Instancia do material do detalhe de precis�o.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* CannonAccuracyMAterial;

	/* Mesh do detalhe de firerate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* CannonFireRateMesh;

	/*Instancia do material do detalhe de firerate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* CannonFireRateMaterial;

#pragma endregion Properties

	
#pragma region Constructor

	/* Constructor padr�o. */
	UProjectileItem();

#pragma endregion Constructor

#pragma region Functions

	/*
	* Fun��o para ativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void ActivateItem();
	virtual void ActivateItem_Implementation();

	/*
	* Fun��o para desativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DeactivateItem();
	virtual void DeactivateItem_Implementation();

	/*
	* Override da fun��o para aplicar os stats do item ativo ao jogador.
	*/
	virtual void ApplyItem_Implementation() override;

	/*
	* Override da fun��o para remover os stats do item passivo ao jogador.
	*/
	virtual void RemoveItem_Implementation() override;

#pragma endregion Functions

};
