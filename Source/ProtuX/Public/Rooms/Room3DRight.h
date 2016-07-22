// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3DRight.generated.h"

/*
*	Classe que representa uma sala com tr�s portas. Sala orientada com a orienta��o para direita (portas na dire��o Oeste/Sul/Leste)
*/
UCLASS()
class PROTUX_API ARoom3DRight : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor
public:
	//Constructor
	ARoom3DRight(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
