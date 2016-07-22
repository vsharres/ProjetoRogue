// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ProjectileItem.generated.h"

/*
* Classe derivada da classe UItem
* Classe que representa um item projetil, que representa o item responsável pelo tiro do jogador. Items de projeteis são ativados pelo jogador explicitamente.
*/
UCLASS()
class PROTUX_API UProjectileItem : public UItem
{
	GENERATED_BODY()

#pragma region Properties
public:

	/* Propriedade indicando se o item está ativo. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bIsActive;

	/* Propriedade indicando se este item projétil é o item padrão(item com qual o jogador começa). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		bool bIsStandardProjectile;

	/* Propriedade que indica a quantidade de energia utilizado pelo item por deltatime. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float EnergyRequired;

	/* Classe do projetil a ser gerado quando o item é ativado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<class AProjectile> Projectile;

	/* Mesh do detalhe do dano. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* CannonDamageMesh;

	/* Instancia do material do detalhe do dano. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* CannonDamageMaterial;

	/* Mesh do detalhe de precisão. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* CannonAccuracyMesh;

	/*Instancia do material do detalhe de precisão.*/
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

	/* Constructor padrão. */
	UProjectileItem();

#pragma endregion Constructor

#pragma region Functions

	/*
	* Função para ativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void ActivateItem();
	virtual void ActivateItem_Implementation();

	/*
	* Função para desativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DeactivateItem();
	virtual void DeactivateItem_Implementation();

	/*
	* Override da função para aplicar os stats do item ativo ao jogador.
	*/
	virtual void ApplyItem_Implementation() override;

	/*
	* Override da função para remover os stats do item passivo ao jogador.
	*/
	virtual void RemoveItem_Implementation() override;

#pragma endregion Functions

};
