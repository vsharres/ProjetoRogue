// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

/*
* Enumera��o que representa o tipo do item, que representa a sua funcionalidade
*/
UENUM(BlueprintType)
enum class ETipoItem : uint8
{
	PASSIVO,
	PROJETIL
};

/*
* Estrutura que representa os stats que um item adiciona aos stats do jogador.
*/
USTRUCT()
struct FItemStats
{
	GENERATED_USTRUCT_BODY()

	/* O quanto o item aumenta a vida atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVida;

	/* O quanto o item aumenta a vida maxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVidaMax;

	/* O quanto o item aumenta a velocidade de movimenta��o do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVel;

	/* O quanto o item aumenta a frequ�ncia de tiro do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaFireRate;

	/* O quanto o item aumenta o dano causado pelo jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaDano;

	/* O quanto o item aumenta a precis�o do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaPrecisao;

	/* O quanto o item aumenta a velocidade do proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVelProjetil;

	/* O quanto o item aumenta a energia atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaEnergia;

	/* O quanto o item aumenta a energia m�xima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaEnergiaMax;

	/* O quanto o item custa para ser comprado na loja. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		int32 Custo;

	/*
	* Overload do operador += para facilitar a adi��o de um item a outro.
	* @param itemStats - Refer�ncia constante ao item a ser adicionado.
	* @return Refer�ncia ao item modificado
	*/
	FORCEINLINE	FItemStats& operator+=(const FItemStats& itemStats)
	{
		this->IncrementaVida += itemStats.IncrementaVida;
		this->IncrementaVidaMax += itemStats.IncrementaVidaMax;
		this->IncrementaVel += itemStats.IncrementaVel;
		this->IncrementaFireRate += itemStats.IncrementaFireRate;
		this->IncrementaDano += itemStats.IncrementaDano;
		this->IncrementaPrecisao += itemStats.IncrementaPrecisao;
		this->IncrementaVelProjetil += itemStats.IncrementaVelProjetil;
		this->IncrementaEnergia += itemStats.IncrementaEnergia;
		this->IncrementaEnergiaMax += itemStats.IncrementaEnergiaMax;

		return *this;

	}

	//Construtor
	FItemStats(float incVidaMax = 0.0f, float incVida = 0.0f, float incVel = 0.0f, float incFire = 0.0f, float incDano = 0.0f, float incPrec = 0.0f, float incVelProj = 0.0f, float incEner = 0, float incEnerMax = 0, int32 custo = 0)
	{
		IncrementaVidaMax = incVidaMax;
		IncrementaVida = incVida;
		IncrementaVel = incVel;
		IncrementaFireRate = incFire;
		IncrementaDano = incDano;
		IncrementaPrecisao = incPrec;
		IncrementaVelProjetil = incVelProj;
		IncrementaEnergia = incEner;
		IncrementaEnergiaMax = incEnerMax;
		Custo = custo;
	}


};

/*
* Classe abstrata que representa um item que pode ser adicionado ao jogador.
*/
UCLASS(BlueprintType, Blueprintable, abstract)
class PROJETOROGUE_API UItem : public UObject
{
	GENERATED_BODY()

public:

#pragma region PROPRIEDADES

	/* Stats do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FItemStats Stats;

	/* Tipo do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		ETipoItem Tipo;

	/* Ponteiro ao jogador que � dono do item. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		TWeakObjectPtr<class AJogador> Jogador;

	/* O Nome do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName NomeItem;

#pragma endregion PROPRIEDADES

#pragma region CONSTRUTOR

	/* Construtor padr�o */
	UItem();

#pragma endregion CONSTRUTOR

#pragma region FUN��ES

	/*
	* Fun��o Get que retorna um array com o nome dos efeitos, essa fun��o � usada para mostrar os efeitos do item na UI do jogo.
	* @return Array de strings com os nomes dos efeitos.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<FString> GetNomeEfeitos();

	/*
	* Fun��o Get que retorna um array com o nome dos efeitos, essa fun��o � usada para mostrar os efeitos do item na UI do jogo.
	* @return Array de strings com os nomes dos efeitos.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<float> GetEfeitos();

	/*
	* Fun��o para inicializar o item.
	* @param inicializador - Ponteiro ao jogador que inicializa o item.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Inicializar Item", Keywords = "Inicializar Item"), Category = "Item")
		void InicializarItem(AJogador* inicializador);

	/*
	* Fun��o para aplicar os stats do item ao jogador.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Aplicar Stats", Keywords = "Aplicar Stats"), Category = "Item")
		void AplicarStats();

	/*
	* Fun��o para remover os stats do item ao jogador.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remover Stats", Keywords = "Remover Stats"), Category = "Item")
		void RemoverStats();

	/*
	* Fun��o para aplicar o item ao jogador.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Aplicar Item", Keywords = "Aplicar item"), Category = "Item")
		void AplicarItem();
	virtual void AplicarItem_Implementation();

	/*
	* Fun��o para remover o item ao jogador.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Remover Item", Keywords = "Remover item"), Category = "Item")
		void RemoverItem();
	virtual void RemoverItem_Implementation();

	/*
	* Fun��o est�tica para instanciar um novo item dentro de uma blueprint.
	* @param WorldContextObject - Ponteiro ao mundo onde o item ser� criado.
	* @param Classe - Classe do item a ser instanciado.
	*/
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instanciar Item", Keywords = "Instanciar item"), Category = Item)
		static UObject* InstanciarItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe);

#pragma endregion FUN��ES

};
