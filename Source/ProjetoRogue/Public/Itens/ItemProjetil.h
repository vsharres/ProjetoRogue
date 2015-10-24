// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ItemProjetil.generated.h"

/*
* Classe derivada da classe UItem
* Classe que representa um item projetil, que representa o item responsável pelo tiro do jogador. Items de projeteis são ativados pelo jogador explicitamente.
*/
UCLASS()
class PROJETOROGUE_API UItemProjetil : public UItem
{
	GENERATED_BODY()

#pragma region PROPRIEDADES
public:

	/* Propriedade indicando se o item está ativo. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		bool bAtivo;

	/* Propriedade indicando se este item projétil é o item padrão(item com qual o jogador começa). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		bool bProjetilPadrao;

	/* Propriedade que indica a quantidade de energia utilizado pelo item por deltatime. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		float EnergiaUtilizada;

	/* Classe do projetil a ser gerado quando o item é ativado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projetil)
		TSubclassOf<class AProjectil> Projetil;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* DetalheDano;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* DetalheDano_Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* DetalhePrecisao;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* DetalhePrecisao_Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* DetalheFireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* DetalheFireRate_Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UStaticMesh* DetalheVelocidadeProj;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Canhao)
		UMaterialInstance* DetalheVelocidadeProj_Material;

#pragma endregion PROPRIEDADES

	
#pragma region CONSTRUTOR

	/* Construtor padrão. */
	UItemProjetil();

#pragma endregion CONSTRUTOR

#pragma region FUNÇÕES

	/*
	* Função para ativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Ativar Item", Keywords = "Ativar item"), Category = "Item")
		void AtivarItem();
	virtual void AtivarItem_Implementation();

	/*
	* Função para desativar o item.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Desativar Item", Keywords = "Desativar item"), Category = "Item")
		void DesativarItem();
	virtual void DesativarItem_Implementation();

	/*
	* Override da função para aplicar os stats do item ativo ao jogador.
	*/
	virtual void AplicarItem_Implementation() override;

	/*
	* Override da função para remover os stats do item passivo ao jogador.
	*/
	virtual void RemoverItem_Implementation() override;

#pragma endregion FUNÇÕES

};
