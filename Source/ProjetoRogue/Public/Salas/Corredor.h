// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Corredor.generated.h"

/*
*	Classe derivada da classe AActor.
*	Classe que representa uma dos corredores que conectam as salas. Os corredores são presets que seram gerados pelo gerador de salas.
*/
UCLASS()
class PROJETOROGUE_API ACorredor : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

private:

	/* Offset padrão do corredor, que é utilizado para determinar o transform do corredor durante a geração. */
	UPROPERTY(EditDefaultsOnly)
		float OffsetCorredor;

	/* Escala padrão do corredor, que é utilizado para determinar a escala do corredor durante a geração. */
	UPROPERTY(EditDefaultsOnly)
		FVector EscalaPadrao;

#pragma endregion

#pragma region CONSTRUTOR

public:
	/* Construtor padrão. */
	ACorredor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUNÇÕES

	/*
	* Função Get da escala padrão do corredor.
	* @return FVector com a escala do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		FVector GetEscala();

	/*
	* Função Get do Offset padrão do corredor.
	* @return int32 com o Offset do corredor.
	*/
	UFUNCTION(BlueprintPure, Category = Corredor)
		int32 GetOffset();

#pragma endregion
	
	
};
