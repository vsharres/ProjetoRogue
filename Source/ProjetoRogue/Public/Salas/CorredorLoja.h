// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Salas/Corredor.h"
#include "CorredorLoja.generated.h"

/* Enumeração que representa o tipo de item que está num determinado slot. */
UENUM(BlueprintType)
enum class ESlotTipo : uint8
{
	ENERGIA,
	VIDA,
	ITEM

};

/* Estrutura que represent as propriedades de um dos slots da loja. */
USTRUCT()
struct FLojaSlot{

	GENERATED_USTRUCT_BODY()

	/* Custo do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		int32 Custo;

	/* Efeito do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		float Efeito;

	/* Tipo do item no slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		ESlotTipo Tipo;

	/* Ponteiro ao item no slot. Essa variável apenas é válida se o tipo do slot for ESlotTipo::ITEM */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
	class UItem* Item;

	/* Booleano indicando se o slot foi comprado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		bool bComprado;

	/* Construtor Padrão */
	FLojaSlot() : Custo(10),
		Efeito(0),
		Tipo(ESlotTipo::ENERGIA),
		Item(NULL),
		bComprado(false)
	{}

	/* Destrutor */
	~FLojaSlot()
	{
		Item = NULL;
	}

};

/**
* Classe derivada da classe ACorredor.
* Tipo específico de corredor que contêm um loja. Todo level tem uma loja em um dos seus corredores.
*/
UCLASS()
class PROJETOROGUE_API ACorredorLoja : public ACorredor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

private:

	/* Componente raiz do corredor. Usado para o transform do corredor. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Root")
		USceneComponent* CorredorLoja;

	/* Componente de colisão do trigger que ativa a loja. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Trigger")
		UBoxComponent* TriggerLoja;

	/* Array com as classes dos possíveis itens que podem estar presentes na loja. */
	UPROPERTY(EditDefaultsOnly, Category = "Itens")
		TArray<TSubclassOf<UItem>> Itens;


public:

	/* Array com os slots da loja. O número padrão de slot é 3. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
		TArray<FLojaSlot> Slots;

#pragma endregion

#pragma region CONSTRUTOR

	/* Construtor padrão. */
	ACorredorLoja(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUNÇÕES

	/* Override da função de inicialização do ator. */
	void BeginPlay() override;

	/*
	* Função responsável por inicializar a loja.
	* Esta função criar os itens em cada slot.
	*/
	UFUNCTION()
		void InicializarLoja();
	/*
	* Função para comprar um determinado slot.
	* @param slot - Índice do slot na loja (0 a 2).
	* @param jogador - Ponteiro ao jogador que comprou o slot.
	*/
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void ComprarSlot(int32 slot, class AJogador* jogador);

	/* Função para salvar a loja. Essa função sempre é chamada depois que o jogador comprou um slot. */
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void SalvarLoja();

	/* Função para carregar a loja de um save caso o jogador esteja continuando um jogo. */
	UFUNCTION(BlueprintCallable, Category = "Loja")
		void CarregarLoja();

#pragma endregion

};
