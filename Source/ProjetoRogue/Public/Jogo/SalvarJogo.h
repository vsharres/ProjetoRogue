// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Public/Jogador/Jogador.h"
#include "SalvarJogo.generated.h"

/**
 *
 */
UCLASS()
class PROJETOROGUE_API USalvarJogo : public USaveGame
{
	GENERATED_BODY()

public:

	//Slot
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
		FString SaveSlot;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
		uint32 Userindex;

	//Salas
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		TArray<bool> SalasComInimigos;

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		int32 Seed;

	//Jogador

	UPROPERTY(VisibleAnywhere, Category = "Jogador")
		FJogadorStats Stats;

	UPROPERTY(VisibleAnywhere, Category = "Jogador")
		int32 Moedas;

	UPROPERTY(VisibleAnywhere, Category = "Jogador")
		bool bPossuiChave;

	UPROPERTY(VisibleAnywhere, Category = "Jogador")
		FVector JogadorLocation;

	UPROPERTY(VisibleAnywhere, Category = "Jogador")
		FRotator JogadorRotation;



	//Itens

	UPROPERTY(VisibleAnywhere, Category = "Itens")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	UPROPERTY(VisibleAnywhere, Category = "Itens")
		TArray < TSubclassOf<class UItemPassivo>> ItensPassivos;

	UPROPERTY(VisibleAnywhere, Category = "Itens")
		TSubclassOf < class UItemAtivo> ItemAtivo;

	UPROPERTY(VisibleAnywhere, Category = "Itens")
		bool bItemEncontrado;


	//Construtor
	USalvarJogo(const FObjectInitializer& ObjectInitializer);



};
