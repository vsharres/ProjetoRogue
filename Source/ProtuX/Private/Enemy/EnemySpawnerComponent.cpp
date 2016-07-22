// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnemySpawnerComponent.h"
#include "Enemy.h"

UEnemySpawnerComponent::UEnemySpawnerComponent()
{
	//Inicializando propriedades
	bSpawnRandomly = false;
}

int32 UEnemySpawnerComponent::GetNumEnemies(ERoomDifficulty difficulty)
{
	int32 num;

	switch (difficulty) //retornar o número de inimigos de acordo com a dificuldade
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
	TSubclassOf<AEnemy> classe;

	//selecionar randomicamente um inimigo de acordo com a dificuldade
	switch (difficulty)
	{
	case ERoomDifficulty::NORMAL:
		classe = RandomEnemiesNormal[Stream.FRandRange(0, RandomEnemiesNormal.Num() - 1)]; 
		break;
	case ERoomDifficulty::HARD:
		classe = RandomEnemiesHard[Stream.FRandRange(0, RandomEnemiesHard.Num() - 1)];
		break;
	}

	return classe;
}
