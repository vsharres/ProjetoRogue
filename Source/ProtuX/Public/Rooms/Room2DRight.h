// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2DRight.generated.h"

/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orientação virada para direita (portas na direção Oeste/Sul)
*/
UCLASS()
class PROTUX_API ARoom2DRight : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor

public:
	//Constructor
	ARoom2DRight(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor



};
