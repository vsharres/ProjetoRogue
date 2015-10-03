// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala3P.generated.h"


/*
*	Classe que representa uma sala com três portas. Sala orientada com a orientação padrão (portas na direção Oeste/Sul/Norte)
*/
UCLASS()
class PROJETOROGUE_API ASala3P : public ASala
{
	GENERATED_BODY()

#pragma region CONSTRUTOR
public:
	//Construtor
	ASala3P(const FObjectInitializer& ObjectInitializer);
#pragma endregion CONSTRUTOR

};
