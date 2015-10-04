// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "PickUpEnergia.generated.h"

/*
* Classe derivada da classe PickUp.
* Classe que representa o pickup que regenera a energia do jogador.
*/
UCLASS()
class PROJETOROGUE_API APickUpEnergia : public APickUp
{
	GENERATED_BODY()

#pragma region CONSTRUTOR

	/*Construtor Padr�o. */
	APickUpEnergia(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUN��ES
	
	/*
	* Fun��o delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da fun��o determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion FUN��ES

};
