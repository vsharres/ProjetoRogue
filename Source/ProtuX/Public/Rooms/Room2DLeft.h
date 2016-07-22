// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2DLeft.generated.h"

/*
*	Classe que representa uma sala com duas portas. Sala orientada com a orientação para esquerda (portas na direção Oeste/Norte)
*/
UCLASS()
class PROTUX_API ARoom2DLeft : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor

public:
	//Constructor
	ARoom2DLeft(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor





};

