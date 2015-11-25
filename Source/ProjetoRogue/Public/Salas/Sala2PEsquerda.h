// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala2PEsquerda.generated.h"

/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orientação para esquerda (portas na direção Oeste/Norte)
*/
UCLASS()
class PROJETOROGUE_API ASala2PEsquerda : public ASala
{
	GENERATED_BODY()

#pragma region CONSTRUTOR

public:
	//Construtor
	ASala2PEsquerda(const FObjectInitializer& ObjectInitializer);
#pragma endregion CONSTRUTOR





};

