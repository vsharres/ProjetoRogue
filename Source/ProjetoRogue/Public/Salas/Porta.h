// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Porta.generated.h"


/* Classe que representa uma das portas das salas. */
UCLASS()
class PROJETOROGUE_API APorta : public AActor
{
	GENERATED_BODY()
	
#pragma region PROPRIEDADES

public:	

	/* Booleando que indica se a porta deve ser aberta. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bAbrirPorta;

	/* Booleando que indica se a porta deve ser aberta. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bFecharPorta;

	/* Booleando que indica se a porta deve ser trancada. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bPortaTrancada;

	/* Ponteiro a sala que a porta pertence. */
	UPROPERTY(BlueprintReadWrite, Category = "Sala")
	class ASala* SalaPai;

#pragma endregion PROPRIEDADES

#pragma region FUNÇÕES

public:

	/*
	* Evento disparado para trancar a porta.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Trancar Porta", Keywords = "Trancar Porta"), Category = "Porta")
		void TrancarPorta();

	/*
	* Evento disparado para destrancar a porta.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Porta", Keywords = "Destrancar Porta"), Category = "Porta")
		void DestrancarPorta();


	// Construtor
	APorta();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
#pragma endregion FUNÇÕES
	
};
