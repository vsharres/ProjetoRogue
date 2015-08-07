// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Porta.generated.h"

UCLASS()
class PROJETOROGUE_API APorta : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bAbrirPorta;

	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bFecharPorta;

	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bPortaTrancada;

	UPROPERTY(BlueprintReadWrite, Category = "Sala")
	class ASala* SalaPai;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Trancar Porta", Keywords = "Trancar Porta"), Category = "Porta")
		virtual void TrancarPorta();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Porta", Keywords = "Destrancar Porta"), Category = "Porta")
		virtual void DestrancarPorta();


	// Sets default values for this actor's properties
	APorta();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
