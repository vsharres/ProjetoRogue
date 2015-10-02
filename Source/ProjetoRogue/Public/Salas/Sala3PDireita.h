// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala3PDireita.generated.h"

/*
*	Classe que representa uma sala com tr�s portas. Sala orientada com a orienta��o para direita (portas na dire��o Oeste/Sul/Leste)
*/
UCLASS()
class PROJETOROGUE_API ASala3PDireita : public ASala
{
	GENERATED_BODY()

public:
	//Construtor
	ASala3PDireita(const FObjectInitializer& ObjectInitializer);


};
