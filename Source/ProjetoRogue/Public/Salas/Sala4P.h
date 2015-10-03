// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sala.h"
#include "Sala4P.generated.h"

/*
*	Classe que representa uma sala com quatro portas. Sala orientada com a orienta��o padr�o (portas na dire��o Oeste/Norte/Leste/Sul)
*/
UCLASS()
class PROJETOROGUE_API ASala4P : public ASala
{
	GENERATED_BODY()
#pragma region CONSTRUTOR

public:
	//Construtor
	ASala4P(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

};
