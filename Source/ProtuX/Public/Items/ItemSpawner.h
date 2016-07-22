// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/*
* Classe respons�vel por fazer a gera��o do item do level.
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

	/* Componente de colis�o do gerador de itens. */
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Collider;


public:

	/* Seed de gera��o do item. Este seed � o mesmo utilizado pelo gerador de salas. */
	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;

#pragma endregion Properties
	
#pragma region Constructor

	/* Constructor padr�o. */
	AItemSpawner(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

};
