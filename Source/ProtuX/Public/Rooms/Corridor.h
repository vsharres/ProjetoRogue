// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Corridor.generated.h"

/*
*	Classe derivada da classe AActor.
*	Classe que representa uma dos corredores que conectam as salas. Os corredores são presets que seram gerados pelo gerador de salas.
*/
UCLASS()
class PROTUX_API ACorridor : public AActor
{
	GENERATED_BODY()

#pragma region Properties

private:

	/* Offset padrão do corredor, que é utilizado para determinar o transform do corredor durante a geração. */
	UPROPERTY(EditDefaultsOnly)
		float OffsetCorridor;

	/* Escala padrão do corredor, que é utilizado para determinar a escala do corredor durante a geração. */
	UPROPERTY(EditDefaultsOnly)
		FVector StandardScale;

#pragma endregion

#pragma region Constructor

public:
	/* Constructor padrão. */
	ACorridor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Functions

	/*
	* Função Get da escala padrão do corredor.
	* @return FVector com a escala do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		FVector GetScale();

	/*
	* Função Get do Offset padrão do corredor.
	* @return int32 com o Offset do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		int32 GetOffset();

#pragma endregion
	
	
};
