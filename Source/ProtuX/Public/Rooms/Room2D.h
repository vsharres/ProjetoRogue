// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2D.generated.h"


/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orientação padrão (portas na direção Oeste/Leste)
*/
UCLASS()
class PROTUX_API ARoom2D : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor
public:

	// Constructor
	ARoom2D(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
