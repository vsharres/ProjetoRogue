// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ProtuXGameMode.generated.h"

/** Enumeração resposável pelo estado atual do jogo. */
UENUM()
enum class EGameState : uint8{
	MAINMENU,
	NEWGAME,
	CONTINUEGAME,
	NEXTLEVEL,
	RESTART,
	GAMEOVER
};

/** Classe derivada da classe AGameMode
*  Classe responsável por gerências as regras e o estado atual do jogo e fazendo a alteração dos leveis.
*/
UCLASS()
class PROTUX_API AProtuXGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	/** Estado atual do jogo. */
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		EGameState State;

public:
	/** Booleano de teste usado para testar o jogo sem salvar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNoSave;
	/** Booleano indicando se o jogo é um novo jogo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bIsNewGame;
	/** Número de jogos iniciados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 NumGames;
	/** Número do level atual. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 CurrentLevel;


	AProtuXGameMode(const FObjectInitializer& ObjectInitializer);
	
	/**
	* Função de get do estado atual do jogo.
	* @return EJogoEstado atual.
	*/
	UFUNCTION()
		EGameState GetGameState() const;

	/**
	* Função para setar o estado do jogo atual.
	* @param NovoEstado - Enumerador EJogoEstado com o novo estado.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void SetGameState(EGameState newState);

	/**
	* Função para atualizar o estado do jogo. Função apenas realizada pela classe pai.
	* @param NovoEstado - Enumerador EJogoEstado com o novo estado.
	*/
	UFUNCTION()
		void UpdateState(EGameState newState);

	/**
	* Função para fazer o load do profile de um novo jogo.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNewGame();
	
	/**
	* Função para fazer o load do profile para continuar um jogo.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadContinueGame();
	
	/**
	* Função para fazer o load do profile para a próxima fase.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNextLevel();
	
};
