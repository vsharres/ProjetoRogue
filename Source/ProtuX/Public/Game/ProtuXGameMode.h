// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ProtuXGameMode.generated.h"

/** Enum of the state of the game. */
UENUM()
enum class EGameState : uint8{
	MAINMENU,
	NEWGAME,
	CONTINUEGAME,
	NEXTLEVEL,
	RESTART,
	GAMEOVER
};

/**
*	Class inherited from AGameMode
*	Class responsible for managing the rules of the game, its current state, saving, loading and changing of levels.
*/
UCLASS()
class PROTUX_API AProtuXGameMode : public AGameMode
{
	GENERATED_BODY()

#pragma region Properties

private:
	/** Game current state. */
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		EGameState State;

public:
	/** Testing variable use to test the game without saving. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNoSave;

	/** Boolean indicating if the current game is a new game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bIsNewGame;

	/** Number of games initiated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 NumGames;

	/** Current level of the game */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 CurrentLevel;

#pragma endregion Properties

#pragma region Constructor

	/** Default Constructor */
	AProtuXGameMode(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion Constructor

#pragma region Functions

	/**
	* Get function to get the current state of the game
	* @return EJogoEstado current state.
	*/
	UFUNCTION()
		EGameState GetGameState() const;

	/**
	* Set function to set a new game state
	* @param newState - new state of the game
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void SetGameState(EGameState newState);

	/**
	* Function to update the game state. Function only called by the Game Mode.
	* @param NovoEstado - New state of the game
	*/
	UFUNCTION()
		void UpdateState(EGameState newState);

	/**
	* Function to load a new game from a save game slot
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNewGame();
	
	/**
	* Function to load a previous game to continue
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadContinueGame();
	
	/**
	* Function to load the next level of the game.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNextLevel();
	
#pragma endregion Functions

};
