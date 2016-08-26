// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BillboardComponent.h"
#include "Room.h"
#include "EnemySpawnerComponent.generated.h"

/**
 * Class inherited from UBillboardComponent
 * Room spawner component responsible for the enemy spawn location and logic.
 */
UCLASS(ClassGroup = "EnemySpawner", meta = (BlueprintSpawnableComponent))
class PROTUX_API UEnemySpawnerComponent : public UBillboardComponent
{
	GENERATED_BODY()

#pragma region Properties

public:

	/** Boolean to generate the enemy randomly */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		bool bSpawnRandomly;

	/** Array with the enemy normal classes that can be generated.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesNormal;

	/** Array with the enemy hard classes that can be generated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TArray<TSubclassOf<class AEnemy>> RandomEnemiesHard;

	/** Class of the normal enemy to be used not randomly */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TSubclassOf<AEnemy> EnemiesNormal;

	/** Class of the hard enemy to be used not randomly*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
		TSubclassOf<AEnemy> EnemiesHard;

#pragma endregion Properties
	
#pragma region Construtor

	/** Default constructor. */
	UEnemySpawnerComponent();

#pragma endregion Construtor

#pragma region Functions

	/**
	* Function to get the number of enemies.
	* @param difficulty - Difficulty of enemies to get
	* @return The number of enemies
	*/
	UFUNCTION(BlueprintPure, Category = "EnemySpawner")
		int32 GetNumEnemies(ERoomDifficulty difficulty);

	/**
	* Function to select the enemy that will be generated randomly from the enemy array of a given difficulty
	* @param Stream - Random stream generator
	* @param difficulty - Difficulty of the room that is generating the enemy
	* @return The class of the enemy to be generated
	*/
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
	TSubclassOf<AEnemy> SelectEnemyRand(FRandomStream& Stream, ERoomDifficulty difficulty);

#pragma endregion Functions

};
