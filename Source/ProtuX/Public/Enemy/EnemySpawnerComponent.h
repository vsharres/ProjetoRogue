// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BillboardComponent.h"
#include "Room.h"
#include "EnemySpawnerComponent.generated.h"

/*
 * Classe derivada da UBillboardComponent
 * Componente da sala respons�vel por fazer o spawn dos inimigos.
 */
UCLASS(ClassGroup = InimigoSpawner, meta = (BlueprintSpawnableComponent))
class PROTUX_API UEnemySpawnerComponent : public UBillboardComponent
{
	GENERATED_BODY()

#pragma region Propriedades

public:

	/* Booleano para gerar o inimigo randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		bool bSpawnRandomly;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesNormal;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesHard;

	/* Classe do inimigo a ser gerado n�o randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TSubclassOf<AEnemy> EnemiesNormal;

	/* Classe do inimigo a ser gerado n�o randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TSubclassOf<AEnemy> EnemiesHard;

#pragma endregion Propriedades
	
#pragma region Construtor

	/* Construtor padr�o. */
	UEnemySpawnerComponent();

#pragma endregion Construtor

#pragma region Fun��es

	UFUNCTION()
		int32 GetNumEnemies(ERoomDifficulty difficulty);

	/*
	* Fun��o para selecionar o inimigo que vai ser gerado randomicamente a partir do array de inimigos.
	* @param Stream - Stream randomico de gera��o.
	*/
	UFUNCTION(BlueprintCallable, Category = InimigoSpawner)
	TSubclassOf<AEnemy> SelectEnemyRand(FRandomStream& Stream, ERoomDifficulty difficulty);

#pragma endregion Fun��es

};
