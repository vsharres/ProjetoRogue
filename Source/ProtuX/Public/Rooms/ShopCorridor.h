// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rooms/Corridor.h"
#include "ShopCorridor.generated.h"

/* Enumera��o que representa o tipo de item que est� num determinado slot. */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	ENERGY,
	HEALTH,
	ITEM

};

/* Estrutura que represent as propriedades de um dos slots da loja. */
USTRUCT()
struct FShopSlot{

	GENERATED_USTRUCT_BODY()

	/* Custo do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		int32 Cost;

	/* Efeito do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		float Effect;

	/* Tipo do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		ESlotType Type;

	/* Ponteiro ao item no slot. Essa vari�vel apenas � v�lida se o tipo do slot for ESlotTipo::ITEM */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
	class UItem* Item;

	/* Booleano indicando se o slot foi comprado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		bool bBought;

	/* Constructor Padr�o */
	FShopSlot() : Cost(10),
		Effect(0),
		Type(ESlotType::ENERGY),
		Item(NULL),
		bBought(false)
	{}

	/* Destrutor */
	~FShopSlot()
	{
		Item = NULL;
	}

};

/**
* Classe derivada da classe ACorredor.
* Tipo espec�fico de corredor que cont�m um loja. Todo level tem uma loja em um dos seus corredores.
*/
UCLASS()
class PROTUX_API AShopCorridor : public ACorridor
{
	GENERATED_BODY()

#pragma region Properties

private:

	/* Componente raiz do corredor. Usado para o transform do corredor. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Root")
		USceneComponent* ShopCorridorRoot;

	/* Componente de colis�o do trigger que ativa a loja. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Trigger")
		UBoxComponent* ShopTrigger;

	/* Array com as classes dos poss�veis itens que podem estar presentes na loja. */
	UPROPERTY(EditDefaultsOnly, Category = "Itens")
		TArray<TSubclassOf<UItem>> Items;


public:

	/* Array com os slots da loja. O n�mero padr�o de slot � 3. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
		TArray<FShopSlot> Slots;

#pragma endregion

#pragma region Constructor

	/* Constructor padr�o. */
	AShopCorridor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Functions

	/* Override da fun��o de inicializa��o do ator. */
	void BeginPlay() override;

	/*
	* Fun��o respons�vel por inicializar a loja.
	* Esta fun��o criar os itens em cada slot.
	*/
	UFUNCTION()
		void InitializeShop();
	/*
	* Fun��o para comprar um determinado slot.
	* @param slot - �ndice do slot na loja (0 a 2).
	* @param jogador - Ponteiro ao jogador que comprou o slot.
	*/
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void BuySlot(int32 slot, class AProtuXPlayer* player);

	/* Fun��o para salvar a loja. Essa fun��o sempre � chamada depois que o jogador comprou um slot. */
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void SaveShopState();

	/* Fun��o para carregar a loja de um save caso o jogador esteja continuando um jogo. */
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void LoadShopState();

#pragma endregion

};
