// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala3PEsquerda.generated.h"

/*
*	Classe que representa uma sala com três portas. Sala orientada com a orientação para esquerda (portas na direção Oeste/Norte/Leste)
*/
UCLASS()
class PROJETOROGUE_API ASala3PEsquerda : public ASala
{
	GENERATED_BODY()

public:
	//Construtor
	ASala3PEsquerda(const FObjectInitializer& ObjectInitializer);


};
