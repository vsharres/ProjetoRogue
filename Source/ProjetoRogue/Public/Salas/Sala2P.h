// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala2P.generated.h"



/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orientação padrão (portas na direção Oeste/Leste)
*/
UCLASS()
class PROJETOROGUE_API ASala2P : public ASala
{
	GENERATED_BODY()

#pragma region CONSTRUTOR
public:

	// Construtor
	ASala2P(const FObjectInitializer& ObjectInitializer);
#pragma endregion CONSTRUTOR


};
