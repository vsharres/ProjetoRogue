// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class PROJETOROGUE_API AItemSpawner : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = Itens)
	class UItem* ItemGerado;

	UPROPERTY(BlueprintReadWrite, Category = Itens)
		TSubclassOf<UItem> TipoItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Itens)
		TArray<TSubclassOf<UItem>> PossiveisItens;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Colisor;

	UPROPERTY(VisibleDefaultsOnly, Category = Sprite)
		UBillboardComponent* Sprite;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	// Sets default values for this actor's properties
	AItemSpawner(const FObjectInitializer& ObjectInitializer);


};
