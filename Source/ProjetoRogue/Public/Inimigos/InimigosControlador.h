// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "InimigosControlador.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AInimigosControlador : public AAIController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sala")
	TWeakObjectPtr<class ASala> SalaPai;


	AInimigosControlador();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Desativar Inimigo", Keywords = "Desativar Inimigo"), Category = "Inimigos Controlador")
		void DesativarInimigo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Ativar Inimigo", Keywords = "Ativar Inimigo"), Category = "Inimigos Controlador")
		void AtivarInimigo();
	
};
