// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class ETipoItem : uint8
{
	PASSIVO,
	ATIVO
};

USTRUCT()
struct FItemStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVidaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaDano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaParticula;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVelProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		int32 IncrementaEnergia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		float IncrementaVida;

	FORCEINLINE	FItemStats& operator+=(const FItemStats& itemStats)
	{
		this->IncrementaVidaMax += itemStats.IncrementaVidaMax;
		this->IncrementaVel += itemStats.IncrementaVel;
		this->IncrementaFireRate += itemStats.IncrementaFireRate;
		this->IncrementaRange += itemStats.IncrementaRange;
		this->IncrementaDano += itemStats.IncrementaDano;
		this->IncrementaParticula += itemStats.IncrementaParticula;
		this->IncrementaVelProjetil += itemStats.IncrementaVelProjetil;
		this->IncrementaEnergia += itemStats.IncrementaEnergia;
		this->IncrementaVida += itemStats.IncrementaVida;

		return *this;

	}

	FItemStats(float incVidaMax = 0.0f, float incVida = 0.0f, float incVel = 0.0f, float incFire = 0.0f, float incRange = 0.0f, float incDano = 0.0f, float incPart = 0.0f, float incVelProj = 0.0f, int32 incEner = 0)
	{
		IncrementaVidaMax = incVidaMax;
		IncrementaVida = incVida;
		IncrementaVel = incVel;
		IncrementaFireRate = incFire;
		IncrementaRange = incRange;
		IncrementaDano = incDano;
		IncrementaParticula = incPart;
		IncrementaVelProjetil = incVelProj;
		IncrementaEnergia = incEner;
	}


};

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROJETOROGUE_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FItemStats Stats;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		ETipoItem Tipo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class AJogador* Jogador;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FName NomeItem;

	UItem();

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
		static UObject* InstanciarItem(UObject* WorldContextObject, TSubclassOf<UItem> Classe);


};
