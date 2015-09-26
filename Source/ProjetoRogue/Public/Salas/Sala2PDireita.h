// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala2PDireita.generated.h"

/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orienta��o virada para direita (portas na dire��o Oeste/Sul)
*/
UCLASS()
class PROJETOROGUE_API ASala2PDireita : public ASala
{
	GENERATED_BODY()

public:
	//Construtor
	ASala2PDireita(const FObjectInitializer& ObjectInitializer);



};
