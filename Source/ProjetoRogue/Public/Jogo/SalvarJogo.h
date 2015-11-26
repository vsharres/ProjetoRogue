// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Jogador.h"
#include "SalvarJogo.generated.h"

/**
 * Classe para criar o objeto respons�vel em salvar o jogo.
 */
UCLASS(Blueprintable)
class PROJETOROGUE_API USalvarJogo : public USaveGame
{
	GENERATED_BODY()

#pragma region Propriedades
public:
	//Slot

	/* Nome do slot do jogo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		FString SaveSlot;

	/* �ndice do jogador no slot. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
		int32 Userindex;

	//GameMode

	/* Booleano indicando se o jogo � um novo jogo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bNovoJogo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		bool bContinuarJogo;

	/* N�mero de jogos no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
		int32 NumJogos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 LevelAtual;

	//Salas

	/* Array com as salas que tem inimigos. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<bool> SalasComInimigos;

	/* Seed do level que foi gerado no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 Seed;

	/* M�ximo n�mero de salas que podem ser geradas no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 MaxNumSalas;

	/* M�nimo n�mero de salas que podem ser geradas no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		int32 MinNumSalas;

	//Jogador

	/* Stats do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FJogadorStats Stats;

	/* Scrap do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		int32 Scrap;

	/* Booleano indicando se o jogador tem a chave no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		bool bPossuiChave;

	/* Posi��o do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FVector JogadorLocation;

	/* Rota��o do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jogador")
		FRotator JogadorRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Boss)
		bool bBossDerrotado;

	//Itens

	/* Refer�ncia ao asset do projetil atual do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		FString ProjetilEncontrado_Referencia;

	/* Array de refer�ncias aos assets dos itens passivos do jogador no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TArray <FString> ItensPassivos_Referencias;

	/* Boolenaod indicando se o item foi encontrado no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		bool bItemEncontrado;

	/* Array de booleanos indicando quais slots das salas foram comprados no save. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Itens")
		TArray<bool> ItensComprados;

	//SONS
	
	/* Booleano para desativar todos os sons. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		bool bMute;

	/* Volume total dos sons. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float MasterVol;

	/* Volume da m�sica. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float MusicVol;

	/*Volume dos efeitos. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Som")
		float EffectsVol;

#pragma endregion Propriedades

#pragma region Construtor
	/* Construtor padr�o. */
	USalvarJogo(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor


};
