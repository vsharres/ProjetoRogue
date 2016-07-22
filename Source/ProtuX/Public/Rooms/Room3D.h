// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3D.generated.h"


/*
*	Classe que representa uma sala com tr�s portas. Sala orientada com a orienta��o padr�o (portas na dire��o Oeste/Sul/Norte)
*/
UCLASS()
class PROTUX_API ARoom3D : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor
public:
	//Constructor
	ARoom3D(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor



};
