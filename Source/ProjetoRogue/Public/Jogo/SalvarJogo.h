// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Public/Jogador/Jogador.h"
#include "SalvarJogo.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class PROJETOROGUE_API USalvarJogo : public USaveGame
{
	GENERATED_BODY()

public:


	//Slot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		FString SaveSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		int32 Userindex;

	//GameMode
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bNovoJogo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		int32 NumJogos;

	//Salas
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<bool> SalasComInimigos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 Seed;

	//Jogador

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FJogadorStats Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		int32 Moedas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		bool bPossuiChave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FVector JogadorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FRotator JogadorRotation;


	//Itens

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TArray < TSubclassOf<class UItemPassivo>> ItensPassivos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TSubclassOf < class UItemAtivo> ItemAtivo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		bool bItemEncontrado;


	//Construtor
	USalvarJogo(const FObjectInitializer& ObjectInitializer);



};
