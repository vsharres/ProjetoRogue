// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

/*
* Enumera��o que representa o tipo do item, que representa a sua funcionalidade
*/
UENUM(BlueprintType)
enum class EItemType : uint8
{
	PASSIVE,
	PROJECTILE
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
		float AddHealth;

	/* O quanto o item aumenta a vida maxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMaxHealth;

	/* O quanto o item aumenta a velocidade de movimenta��o do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddSpeed;

	/* O quanto o item aumenta a frequ�ncia de tiro do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddFireRate;

	/* O quanto o item aumenta o dano causado pelo jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddDamage;

	/* O quanto o item aumenta a precis�o do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddAccuracy;

	/* O quanto o item aumenta a velocidade do proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMuzzleSpeed;

	/* O quanto o item aumenta a energia atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddEnergy;

	/* O quanto o item aumenta a energia m�xima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float AddMaxEnergy;
	

	/*
	* Overload do operador += para facilitar a adi��o de um item a outro.
	* @param itemStats - Refer�ncia constante ao item a ser adicionado.
	* @return Refer�ncia ao item modificado
	*/
	FORCEINLINE	FItemStats& operator+=(const FItemStats& itemStats)
	{
		this->AddHealth += itemStats.AddHealth;
		this->AddMaxHealth += itemStats.AddMaxHealth;
		this->AddSpeed += itemStats.AddSpeed;
		this->AddFireRate += itemStats.AddFireRate;
		this->AddDamage += itemStats.AddDamage;
		this->AddAccuracy += itemStats.AddAccuracy;
		this->AddMuzzleSpeed += itemStats.AddMuzzleSpeed;
		this->AddEnergy += itemStats.AddEnergy;
		this->AddMaxEnergy += itemStats.AddMaxEnergy;

		return *this;

	}

	//Constructor
	FItemStats(float addHealthMax = 0.0f, float addHealth = 0.0f, float addSpeed = 0.0f, float addFireRate = 0.0f, float addDamage = 0.0f, float addAccuracy = 0.0f, float addMuzzleSpeed = 0.0f, float addEnergy = 0, float addMaxEnergy = 0)
	{
		AddMaxHealth = addHealthMax;
		AddHealth = addHealth;
		AddSpeed = addSpeed;
		AddFireRate = addFireRate;
		AddDamage = addDamage;
		AddAccuracy = addAccuracy;
		AddMuzzleSpeed = addMuzzleSpeed;
		AddEnergy = addEnergy;
		AddMaxEnergy = addMaxEnergy;
	}


};

/*
* Classe abstrata que representa um item que pode ser adicionado ao jogador.
*/
UCLASS(BlueprintType, Blueprintable, abstract)
class PROTUX_API UItem : public UObject
{
	GENERATED_BODY()



#pragma region Properties
public:

	/* Stats do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FItemStats Stats;

	/* Tipo do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		EItemType Type;

	/* Ponteiro ao jogador que � dono do item. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		TWeakObjectPtr<class AProtuXPlayer> Player;

	/* O Nome do item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		FText EffectsDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		int32 Cost;

#pragma endregion Properties

#pragma region Constructor
public:

	/* Constructor padr�o */
	UItem();

#pragma endregion Constructor

#pragma region Functions
public:

	/*
	* Fun��o Get que retorna um array com o nome dos efeitos, essa fun��o � usada para mostrar os efeitos do item na UI do jogo.
	* @return Array de strings com os nomes dos efeitos.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<FString> GetEffectsNames();

	/*
	* Fun��o Get que retorna um array com o nome dos efeitos, essa fun��o � usada para mostrar os efeitos do item na UI do jogo.
	* @return Array de strings com os nomes dos efeitos.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<float> GetEffects();

	/*
	* Fun��o para inicializar o item.
	* @param inicializador - Ponteiro ao jogador que inicializa o item.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Inicializar Item", Keywords = "Inicializar Item"), Category = "Item")
		void InitializeItem(AProtuXPlayer* initializer);

	/*
	* Fun��o para aplicar os stats do item ao jogador.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Aplicar Stats", Keywords = "Aplicar Stats"), Category = "Item")
		void ApplyStats();

	/*
	* Fun��o para remover os stats do item ao jogador.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remover Stats", Keywords = "Remover Stats"), Category = "Item")
		void RemoveStats();

	/*
	* Fun��o para aplicar o item ao jogador.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Aplicar Item", Keywords = "Aplicar item"), Category = "Item")
		void ApplyItem();
	virtual void ApplyItem_Implementation();

	/*
	* Fun��o para remover o item ao jogador.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Remover Item", Keywords = "Remover item"), Category = "Item")
		void RemoveItem();
	virtual void RemoveItem_Implementation();

	/*
	* Fun��o est�tica para instanciar um novo item dentro de uma blueprint.
	* @param WorldContextObject - Ponteiro ao mundo onde o item ser� criado.
	* @param Classe - Classe do item a ser instanciado.
	*/
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instanciar Item", Keywords = "Instanciar item"), Category = Item)
		static UObject* InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe);

#pragma endregion Functions

};
