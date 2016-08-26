// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnemyController.h"
#include "ProtuXGameMode.h"

AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	//Initializing properties
	bIsNewGame = true;
	bNoSave = false;
	CurrentLevel = 0;
}

EGameState AProtuXGameMode::GetGameState() const
{
	return State;
}

void AProtuXGameMode::SetGameState(EGameState newState)
{
	State = newState;

	UpdateState(newState); //update state machine
}

void AProtuXGameMode::UpdateState(EGameState newState)
{
	APlayerController* controller;
	TArray<AActor*> enemyController;

	switch (newState)
	{

	case EGameState::MAINMENU: //loading the main menu
		UGameplayStatics::OpenLevel(this, TEXT("MenuPrincipal"), true);
		break;
	case EGameState::NEWGAME: //Load a new game profile, and load the first level
		LoadNewGame();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		break;
	case EGameState::NEXTLEVEL: //load the next level in the game
		LoadNextLevel();
		UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		break;
	case EGameState::CONTINUEGAME: //continuing a previous game, loading its profile
		LoadContinueGame();

		if (CurrentLevel > 1) //if the game stopped on the first level or not
		{
			UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		}
		else
		{
			UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		}
		break;
	case EGameState::GAMEOVER: //game over screen

		UGameplayStatics::GetAllActorsOfClass(this, AAIController::StaticClass(), enemyController); //find all AI controllers

		for (auto Actor : enemyController) //deactivate every enemy
		{
			AEnemyController* inimgControlador = Cast<AEnemyController>(Actor);

			if (inimgControlador->IsValidLowLevelFast())
			{
				inimgControlador->DeactivateEnemy();
			}
		}

		controller = UGameplayStatics::GetPlayerController(this, 0); //Deactivate player controller

		if (controller->IsValidLowLevelFast())
		{
			controller->SetCinematicMode(true, true, true); //set to cinematic mode
			controller->bShowMouseCursor = true;
		}
		break;
	case  EGameState::RESTART: //Restart the game loading the first level
		LoadNewGame();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), true);
		break;
	default:
		break;
	}
}

void AProtuXGameMode::LoadNewGame()
{
	if (bNoSave) //sanity check
		return;

	//instantiate a save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //if there is no save game slot, create a new one
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex)); //loading save game

	if (SaveInst->IsValidLowLevelFast())
	{
		//loading variables
		SaveInst->bIsNewGame = true;
		SaveInst->bIsContinuingGame = false;
		SaveInst->bHasKey = false;
		SaveInst->bIsBossDefeated = false;
		SaveInst->bHasFoundItem = false;
		SaveInst->ItemsBought.Empty();
		SaveInst->Scrap = 0;
		SaveInst->NumGames += 1;
		SaveInst->CurrentLevel = 1; //current level

		//salving changes made
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

	}
}

void AProtuXGameMode::LoadContinueGame()
{
	if (bNoSave) //sanity check
		return;

	//instantiate a save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bIsNewGame = false;
		SaveInst->bIsContinuingGame = true;
		NumGames = SaveInst->NumGames; 

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXGameMode::LoadNextLevel()
{
	if (bNoSave) //sanity check
		return;

	//instantiate a save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bIsNewGame = false; //as the level is changing, remove the isANewGame flag
		SaveInst->bIsContinuingGame = false;
		SaveInst->CurrentLevel++; //increment the number of the current level.
		SaveInst->bHasFoundItem = false;
		SaveInst->bHasKey = false;
		SaveInst->ItemsBought.Empty();
		SaveInst->bIsBossDefeated = false;

		//Saving
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

