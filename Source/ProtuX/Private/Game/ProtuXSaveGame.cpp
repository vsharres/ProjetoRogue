// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Public/Player/ProtuXPlayer.h"
#include "ProtuXSaveGame.generated.h"

/**
 * Classe para criar o objeto responsável em salvar o jogo.
 */
UCLASS(Blueprintable)
class PROTUX_API UProtuXSaveGame : public USaveGame
{
	GENERATED_BODY()

#pragma region Properties
public:
	//Slot

	/* Nome do slot do jogo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		FString SaveSlot;

	/* Índice do jogador no slot. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		int32 Userindex;

	//GameMode

	/* Booleano indicando se o jogo é um novo jogo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bIsNewGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bIsContinuingGame;

	/* Número de jogos no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		int32 NumGames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 CurrentLevel;

	//Salas

	/* Array com as salas que tem inimigos. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<bool> RoomsWithEnemies;

	/* Seed do level que foi gerado no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 Seed;

	/* Máximo número de salas que podem ser geradas no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 MaxNumRooms;

	/* Mínimo número de salas que podem ser geradas no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 MinNumRooms;

	//Player

	/* Stats do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FPlayerStats Stats;

	/* Scrap do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		int32 Scrap;

	/* Booleano indicando se o jogador tem a chave no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		bool bHasKey;

	/* Posição do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FVector PlayerLocation;

	/* Rotação do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FRotator PlayerRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Boss)
		bool bIsBossDefeated;

	//Itens

	/* Referência ao asset do projetil atual do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		FString FoundProjectileRef;

	/* Array de referências aos assets dos itens passivos do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TArray <FString> PassiveItemsRef;

	/* Boolenaod indicando se o item foi encontrado no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		bool bHasFoundItem;

	/* Array de booleanos indicando quais slots das salas foram comprados no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TArray<bool> ItemsBought;

	//SONS
	
	/* Booleano para desativar todos os sons. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		bool bMute;

	/* Volume total dos sons. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float MasterVol;

	/* Volume da música. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float MusicVol;

	/*Volume dos efeitos. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float EffectsVol;

#pragma endregion Properties

#pragma region Constructor
	/* Constructor padrão. */
	UProtuXSaveGame(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
