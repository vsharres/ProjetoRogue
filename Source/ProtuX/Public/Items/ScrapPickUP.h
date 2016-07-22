// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "ScrapPickUP.generated.h"

/*
* Classe derivada da classe PickUp.
* Classe que representa o pickup que adiciona uma moeda ao jogador.
*/
UCLASS()
class PROTUX_API AScrapPickUP : public APickUp
{
	GENERATED_BODY()

#pragma region Constructor

	/*Constructor Padr�o. */
	AScrapPickUP(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

	/*
	* Fun��o delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da fun��o determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
	void ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Fun��o delegate a ser executada quando o trigger de outline inicia um overlap do jogador.
	* Assinatura da fun��o determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Fun��o delegate a ser executada quando o trigger de outline termina um overlap do jogador.
	* Assinatura da fun��o determinada pelo Delegate OnEndOverlap.
	*/
	UFUNCTION()
		void OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion Functions

};
