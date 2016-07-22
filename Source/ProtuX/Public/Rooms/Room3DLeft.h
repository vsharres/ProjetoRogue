// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3DLeft.generated.h"

/*
*	Classe que representa uma sala com tr�s portas. Sala orientada com a orienta��o para esquerda (portas na dire��o Oeste/Norte/Leste)
*/
UCLASS()
class PROTUX_API ARoom3DLeft : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor
public:
	//Constructor
	ARoom3DLeft(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
