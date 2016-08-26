// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnemySpawnerComponent.h"
#include "Enemy.h"

UEnemySpawnerComponent::UEnemySpawnerComponent()
{
	//Initializing properties
	bSpawnRandomly = false;
}

int32 UEnemySpawnerComponent::GetNumEnemies(ERoomDifficulty difficulty)
{
	int32 num;

	switch (difficulty) //return the number of enemies of a given difficulty
	{
	case ERoomDifficulty::NORMAL:
		num = RandomEnemiesNormal.Num();
		break;
	case ERoomDifficulty::HARD:
		num = RandomEnemiesHard.Num();
		break;
	default:
		num = 0;
		break;
	}

	return num;
}

TSubclassOf<AEnemy> UEnemySpawnerComponent::SelectEnemyRand(FRandomStream& Stream, ERoomDifficulty difficulty)
{
	TSubclassOf<AEnemy> chosenClass;

	//select an enemy of a given difficulty randomly inside the enemies array
	switch (difficulty)
	{
	case ERoomDifficulty::NORMAL:
		chosenClass = RandomEnemiesNormal[Stream.FRandRange(0, RandomEnemiesNormal.Num() - 1)]; 
		break;
	case ERoomDifficulty::HARD:
		chosenClass = RandomEnemiesHard[Stream.FRandRange(0, RandomEnemiesHard.Num() - 1)];
		break;
	}

	return chosenClass;
}
