// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/*
* Classe respons�vel por fazer a gera��o do item do level.
*/
UCLASS()
class PROJETOROGUE_API AItemSpawner : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES
protected:

	/* Ponteiro ao item gerado. */
	UPROPERTY(BlueprintReadWrite, Category = Itens)
	class UItem* ItemGerado;

	/* Classe do item a ser gerado. */
	UPROPERTY(BlueprintReadWrite, Category = Itens)
		TSubclassOf<UItem> TipoItem;

	/* Array com as classes dos itens que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Itens)
		TArray<TSubclassOf<UItem>> PossiveisItens;

	/* Componente de colis�o do gerador de itens. */
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Colisor;


public:

	/* Seed de gera��o do item. Este seed � o mesmo utilizado pelo gerador de salas. */
	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;

#pragma endregion PROPRIEDADES
	
#pragma region CONSTRUTOR

	/* Construtor padr�o. */
	AItemSpawner(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

};
