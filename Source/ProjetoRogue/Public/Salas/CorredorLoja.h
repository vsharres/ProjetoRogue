// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Salas/Corredor.h"
#include "CorredorLoja.generated.h"

UENUM(BlueprintType)
enum class ESlotTipo: uint8
{
	ENERGIA,
	VIDA,
	ITEM

};

USTRUCT()
struct FLojaSlot{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		int32 Custo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		int32 Efeito;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		ESlotTipo Tipo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
	class UItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LojaSlot Struct")
		bool bComprado;

	FLojaSlot() : Custo(10),
		Efeito(0),
		Tipo(ESlotTipo::ENERGIA),
		Item(nullptr),
		bComprado(false)
	{}

	~FLojaSlot()
	{
		Item = nullptr;
	}


};

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API ACorredorLoja : public ACorredor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Root")
		USceneComponent* CorredorLoja;

	UPROPERTY(VisibleDefaultsOnly, Category ="Trigger")
		UBoxComponent* TriggerLoja;

	UPROPERTY(EditDefaultsOnly, Category = "Itens")
		TArray<TSubclassOf<UItem>> Itens;
	

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Slots")
		TArray<FLojaSlot> Slots;

	ACorredorLoja(const FObjectInitializer& ObjectInitializer);

	void BeginPlay() override;

	UFUNCTION()
		void InicializarLoja();

	UFUNCTION()
		void ComprarSlot(int32 slot, class AJogador* jogador);

	UFUNCTION()
		void SalvarLoja();

	UFUNCTION()
		void CarregarLoja();
	
	
};
