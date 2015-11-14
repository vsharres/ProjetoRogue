// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "InimigosControlador.generated.h"

/**
 * Classe derivada da classe AAIController.
 * Controlador dos inimigos, responsável pela AI dos inimigos.
 */
UCLASS()
class PROJETOROGUE_API AInimigosControlador : public AAIController
{
	GENERATED_BODY()
	
#pragma region Propriedades
public:
	/* Ponteiro a sala pai do controlador. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sala")
	TWeakObjectPtr<class ASala> SalaPai;
#pragma endregion Propriedades

#pragma region Construtor
	/* Construtor Padrão. */
	AInimigosControlador();
#pragma endregion Construtor

#pragma region Funções

	/* Evento disparado para desativar o inimigo controlado. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Desativar Inimigo", Keywords = "Desativar Inimigo"), Category = "Inimigos Controlador")
		void DesativarInimigo();

	/* Evento disparado para ativar o inimigo controlador. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Ativar Inimigo", Keywords = "Ativar Inimigo"), Category = "Inimigos Controlador")
		void AtivarInimigo();
#pragma endregion Funções
	
};
