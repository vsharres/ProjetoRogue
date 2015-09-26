// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala3PDireita.generated.h"

/*
*	Classe que representa uma sala com três portas. Sala orientada com a orientação para direita (portas na direção Oeste/Sul/Leste)
*/
UCLASS()
class PROJETOROGUE_API ASala3PDireita : public ASala
{
	GENERATED_BODY()

public:
	//Construtor
	ASala3PDireita(const FObjectInitializer& ObjectInitializer);


};
