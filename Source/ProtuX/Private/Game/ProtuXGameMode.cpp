// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "EnemyController.h"
#include "ProtuXGameMode.h"

AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades.
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
	State = newState; //Set novo estado

	UpdateState(newState); //Atualizar state machine
}

void AProtuXGameMode::UpdateState(EGameState newState)
{
	APlayerController* controller; //Controlador do jogador
	TArray<AActor*> enemyController; //Controladores dos inimigos

	switch (newState)
	{

	case EGameState::MAINMENU: //Abrir o menu principal
		UGameplayStatics::OpenLevel(this, TEXT("MenuPrincipal"), true);
		break;
	case EGameState::NEWGAME: //Fazer o load do profile de novo jogo e abrir o level inicial
		LoadNewGame();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		break;
	case EGameState::NEXTLEVEL: //Fazer o load do profile de nova fase e abrir o level.
		LoadNextLevel();
		UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		break;
	case EGameState::CONTINUEGAME:
		LoadContinueGame();
		if (CurrentLevel > 1)
		{
			UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		}
		else
		{
			UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		}
		break;
	case EGameState::GAMEOVER: 

		UGameplayStatics::GetAllActorsOfClass(this, AAIController::StaticClass(), enemyController);

		for (auto Actor : enemyController) //Desativar todos os inimigos
		{
			AEnemyController* inimgControlador = Cast<AEnemyController>(Actor);

			if (inimgControlador->IsValidLowLevelFast())
			{
				inimgControlador->DeactivateEnemy();
			}
		}

		controller = UGameplayStatics::GetPlayerController(this, 0); //Desativar o controle do jogador.

		if (controller->IsValidLowLevelFast())
		{
			controller->SetCinematicMode(true, true, true);
			controller->bShowMouseCursor = true;
		}
		break;
	case  EGameState::RESTART: //Fazer o load do profile de novo jogo e o level inicial.
		LoadNewGame();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), true);
		break;
	default:
		break;
	}
}

void AProtuXGameMode::LoadNewGame()
{
	if (bNoSave)
		return;

	//Criando o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //Case o save não exista, criar um novo.
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast()) 
	{
		SaveInst->bIsNewGame = true; //Por ser um novo jogo, o save game está como jogo novo.
		SaveInst->bIsContinuingGame = false;
		SaveInst->bHasKey = false;
		SaveInst->bIsBossDefeated = false;
		SaveInst->bHasFoundItem = false;
		SaveInst->ItemsBought.Empty();
		SaveInst->Scrap = 0;
		SaveInst->NumGames += 1;	
		SaveInst->CurrentLevel = 1; //Level atual
		
		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

	}
}

void AProtuXGameMode::LoadContinueGame()
{
	if (bNoSave)
		return;

	//Criando o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bIsNewGame = false;
		SaveInst->bIsContinuingGame = true;
		NumGames = SaveInst->NumGames; //Nao incrementar o número de jogos.
		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXGameMode::LoadNextLevel()
{
	if (bNoSave)
		return;
	
	//Criando o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bIsNewGame = false; //por ser uma transição para a proxima fase, não incrementar o número de jogos.
		SaveInst->bIsContinuingGame = false;
		SaveInst->CurrentLevel++; //Incrementar o level atual.
		SaveInst->bHasFoundItem = false;
		SaveInst->bHasKey = false;
		SaveInst->ItemsBought.Empty();
		SaveInst->bIsBossDefeated = false;

		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

