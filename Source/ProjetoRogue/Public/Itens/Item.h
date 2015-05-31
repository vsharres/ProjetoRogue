// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class ETipoItem : uint8
{
	CHAVE,
	ENERGIA,
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
		this->IncrementaEnergia += itemStats.IncrementaEnergia;
		this->IncrementaVida += itemStats.IncrementaVida;

		return *this;
		
	}

	FItemStats(float incVida = 0.0f, float incVel = 0.0f, float incFire =0.0f,float incRange =0.0f, float incDano =0.0f, float incPart =0.0f, int32 incEner = 0)
	{
		IncrementaVida = incVida;
		IncrementaVel = incVel;
		IncrementaFireRate = incFire;
		IncrementaRange = incRange;
		IncrementaDano = incDano;
		IncrementaParticula = incPart;
		IncrementaEnergia = incEner;
	}
	

};

UCLASS(Abstract)
class PROJETOROGUE_API AItem : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		ETipoItem Tipo;
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
