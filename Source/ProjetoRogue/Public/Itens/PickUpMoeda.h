// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "PickUpMoeda.generated.h"

/*
* Classe derivada da classe PickUp.
* Classe que representa o pickup que adiciona uma moeda ao jogador.
*/
UCLASS()
class PROJETOROGUE_API APickUpMoeda : public APickUp
{
	GENERATED_BODY()

#pragma region CONSTRUTOR

	/*Construtor Padr�o. */
	APickUpMoeda(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUN��ES

	/*
	* Fun��o delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da fun��o determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
	void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Fun��o delegate a ser executada quando o trigger de outline inicia um overlap do jogador.
	* Assinatura da fun��o determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Fun��o delegate a ser executada quando o trigger de outline termina um overlap do jogador.
	* Assinatura da fun��o determinada pelo Delegate OnEndOverlap.
	*/
	UFUNCTION()
		void OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion FUN��ES

};
