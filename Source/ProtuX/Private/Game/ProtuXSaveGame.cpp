// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProtuXSaveGame.h"

UProtuXSaveGame::UProtuXSaveGame(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades de um save game.
	SaveSlot = "ProtuX_Save";
	Userindex = 0;

	NumGames = 0;
	CurrentLevel = 0;
	bIsNewGame = true;
	bIsContinuingGame = false;

	MaxNumRooms = 5;
	MinNumRooms = 5;

	bIsBossDefeated = false;

	ItemsBought.AddDefaulted(3);

	bMute = false;
	MasterVol = 1.0f;
	MusicVol = 1.0f;
	EffectsVol = 1.0f;
}