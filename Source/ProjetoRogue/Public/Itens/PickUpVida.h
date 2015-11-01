// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "PickUpVida.generated.h"

/*
* Classe derivada da classe PickUp.
* Classe que representa o pickup que regenera a vida do jogador.
*/
UCLASS()
class PROJETOROGUE_API APickUpVida : public APickUp
{
	GENERATED_BODY()

#pragma region CONSTRUTOR
	
	/*Construtor Padrão. */
	APickUpVida(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUNÇÕES

	/*
	* Função delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da função determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
	void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion FUNÇÕES
};
