// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Corredor.generated.h"

/*
*	Classe derivada da classe AActor.
*	Classe que representa uma dos corredores que conectam as salas. Os corredores s�o presets que seram gerados pelo gerador de salas.
*/
UCLASS()
class PROJETOROGUE_API ACorredor : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

private:

	/* Offset padr�o do corredor, que � utilizado para determinar o transform do corredor durante a gera��o. */
	UPROPERTY(EditDefaultsOnly)
		float OffsetCorredor;

	/* Escala padr�o do corredor, que � utilizado para determinar a escala do corredor durante a gera��o. */
	UPROPERTY(EditDefaultsOnly)
		FVector EscalaPadrao;

#pragma endregion

#pragma region CONSTRUTOR

public:
	/* Construtor padr�o. */
	ACorredor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUN��ES

	/*
	* Fun��o Get da escala padr�o do corredor.
	* @return FVector com a escala do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		FVector GetEscala();

	/*
	* Fun��o Get do Offset padr�o do corredor.
	* @return int32 com o Offset do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		int32 GetOffset();

#pragma endregion
	
	
};
