// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala3PEsquerda.generated.h"

/*
*	Classe que representa uma sala com tr�s portas. Sala orientada com a orienta��o para esquerda (portas na dire��o Oeste/Norte/Leste)
*/
UCLASS()
class PROJETOROGUE_API ASala3PEsquerda : public ASala
{
	GENERATED_BODY()

#pragma region CONSTRUTOR
public:
	//Construtor
	ASala3PEsquerda(const FObjectInitializer& ObjectInitializer);
#pragma endregion CONSTRUTOR


};
