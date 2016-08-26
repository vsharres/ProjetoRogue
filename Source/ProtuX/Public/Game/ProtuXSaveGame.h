// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Public/Player/ProtuXPlayer.h"
#include "ProtuXSaveGame.generated.h"

/**
* Class inherited from USaveGame
* Class responsible for saving the game. The game is saved using a save game object that saves all of the variables needed to load a game.
*/
UCLASS(Blueprintable)
class PROTUX_API UProtuXSaveGame : public USaveGame
{
	GENERATED_BODY()

#pragma region Properties
public:

	/** Name of the save slot */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		FString SaveSlot;

	/** Index of the save slot */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		int32 Userindex;

	/** Boolean value indicating if it is a new game */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bIsNewGame;

	/** Boolean value indicating if the game is continuing a previous session */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bIsContinuingGame;

	/** Number of games saved, used to generate the version of the player name */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		int32 NumGames;

	/** Number of the current level, used to generate the level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		int32 CurrentLevel;

	/** Array of rooms where there are enemies */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		TArray<bool> RoomsWithEnemies;

	/** Seed of the current level */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		int32 Seed;

	/** Max number of rooms used during level generation */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		int32 MaxNumRooms;

	/** Min number of rooms used during level generation */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		int32 MinNumRooms;

	/** Player stats to save */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FPlayerStats Stats;

	/** Player scrap to save */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		int32 Scrap;

	/** Boolean value indicating if the player has found the key */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		bool bHasKey;

	/** Player location to save */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FVector PlayerLocation;

	/** Player rotation to save*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		FRotator PlayerRotation;

	/** Boolean value indicating if the boss of the level was defeated */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boss")
		bool bIsBossDefeated;

	/** Projectile asset reference path, used to load the player projectile item */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		FString FoundProjectileRef;

	/** Passive item assets reference paths array, used to load the player passive items */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TArray <FString> PassiveItemsRef;

	/** Boolean value indicating if the item has been found in the level */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		bool bHasFoundItem;

	/** Boolean array indicading which slots in the shop were bought */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<bool> ItemsBought;
	
	/** Boolean value to mute sound */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
		bool bMute;

	/** Master volume  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
		float MasterVol;

	/** Music volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
		float MusicVol;

	/** Effects volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
		float EffectsVol;

#pragma endregion Properties

#pragma region Constructor
	/** Default Constructor */
	UProtuXSaveGame(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
