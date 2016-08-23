// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BillboardComponent.h"
#include "Room.h"
#include "EnemySpawnerComponent.generated.h"

/*
 * Class inherited from UBillboardComponent
 * Room spawner component responsible for the enemy spawn location and logic.
 */
UCLASS(ClassGroup = "EnemySpawner", meta = (BlueprintSpawnableComponent))
class PROTUX_API UEnemySpawnerComponent : public UBillboardComponent
{
	GENERATED_BODY()

#pragma region Properties

public:

	/* Booleano para gerar o inimigo randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		bool bSpawnRandomly;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesNormal;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesHard;

	/* Classe do inimigo a ser gerado não randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TSubclassOf<AEnemy> EnemiesNormal;

	/* Classe do inimigo a ser gerado não randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TSubclassOf<AEnemy> EnemiesHard;

#pragma endregion Properties
	
#pragma region Construtor

	/* Standard constructor. */
	UEnemySpawnerComponent();

#pragma endregion Construtor

#pragma region Functions

	UFUNCTION()
		int32 GetNumEnemies(ERoomDifficulty difficulty);

	/*
	* Função para selecionar o inimigo que vai ser gerado randomicamente a partir do array de inimigos.
	* @param Stream - Stream randomico de geração.
	*/
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
	TSubclassOf<AEnemy> SelectEnemyRand(FRandomStream& Stream, ERoomDifficulty difficulty);

#pragma endregion Functions

};
