// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/*
* Classe responsável por fazer a geração do item do level.
*/
UCLASS()
class PROTUX_API AItemSpawner : public AActor
{
	GENERATED_BODY()

#pragma region Properties
protected:

	/* Ponteiro ao item gerado. */
	UPROPERTY(BlueprintReadWrite, Category = Itens)
	class UItem* SpawnedItem;

	/* Classe do item a ser gerado. */
	UPROPERTY(BlueprintReadWrite, Category = Itens)
		TSubclassOf<UItem> ItemClass;

	/* Array com as classes dos itens que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Itens)
		TArray<TSubclassOf<UItem>> PossibleItems;

	/* Componente de colisão do gerador de itens. */
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Collider;


public:

	/* Seed de geração do item. Este seed é o mesmo utilizado pelo gerador de salas. */
	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;

#pragma endregion Properties
	
#pragma region Constructor

	/* Constructor padrão. */
	AItemSpawner(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

};
