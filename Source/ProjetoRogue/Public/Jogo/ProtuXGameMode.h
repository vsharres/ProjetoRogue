// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ProtuXGameMode.generated.h"

/* Enumeração resposável pelo estado atual do jogo. */
UENUM()
enum class EJogoEstado : uint8{
	MENUPRINCIPAL,
	NOVOJOGO,
	CONTINUARJOGO,
	PROXIMAFASE,
	REINICIAR,
	GAMEOVER
};

/* Classe derivada da classe AGameMode
*  Classe responsável por gerências as regras e o estado atual do jogo e fazendo a alteração dos leveis.
*/
UCLASS()
class PROJETOROGUE_API AProtuXGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	/* Estado atual do jogo. */
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		EJogoEstado Estado;

public:
	/* Booleano de teste usado para testar o jogo sem salvar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNaoSalvar;
	/* Booleano indicando se o jogo é um novo jogo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNovoJogo;
	/* Número de jogos iniciados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 NumJogos;
	/* Número do level atual. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 LevelAtual;


	AProtuXGameMode(const FObjectInitializer& ObjectInitializer);
	
	/*
	* Função de get do estado atual do jogo.
	* @return EJogoEstado atual.
	*/
	UFUNCTION()
		EJogoEstado GetEstadoJogo() const;

	/*
	* Função para setar o estado do jogo atual.
	* @param NovoEstado - Enumerador EJogoEstado com o novo estado.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void SetEstadoJogo(EJogoEstado NovoEstado);

	/*
	* Função para atualizar o estado do jogo. Função apenas realizada pela classe pai.
	* @param NovoEstado - Enumerador EJogoEstado com o novo estado.
	*/
	UFUNCTION()
		void AtualizarEstado(EJogoEstado NovoEstado);

	/*
	* Função para fazer o load do profile de um novo jogo.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNovoJogo();
	
	/*
	* Função para fazer o load do profile para continuar um jogo.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadContinuarJogo();
	
	/*
	* Função para fazer o load do profile para a próxima fase.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadProximaFase();
	
};
