// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class ETipoItem : uint8
{
	PASSIVO,
	PROJETIL
};

USTRUCT()
struct FItemStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVidaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaDano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaPrecisao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVelProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaEnergia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaEnergiaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		int32 Custo;

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

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, abstract)
class PROJETOROGUE_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FItemStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		ETipoItem Tipo;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	class AJogador* Jogador;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName NomeItem;

	UItem();

	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<FString> GetNomeEfeitos();

	UFUNCTION(BlueprintPure, Category = "Item")
		TArray<float> GetEfeitos();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Inicializar Item", Keywords = "Inicializar Item"), Category = "Item")
		void InicializarItem(AJogador* inicializador);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Aplicar Stats", Keywords = "Aplicar Stats"), Category = "Item")
		void AplicarStats();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remover Stats", Keywords = "Remover Stats"), Category = "Item")
		void RemoverStats();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Aplicar Item", Keywords = "Aplicar item"), Category = "Item")
		void AplicarItem();
		virtual void AplicarItem_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Remover Item", Keywords = "Remover item"), Category = "Item")
		void RemoverItem();
		virtual void RemoverItem_Implementation();

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instanciar Item", Keywords = "Instanciar item"), Category = Item)
		static UObject* InstanciarItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe);

		


};
