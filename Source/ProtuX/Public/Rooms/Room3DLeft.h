// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3DLeft.generated.h"

/*
*	Classe que representa uma sala com três portas. Sala orientada com a orientação para esquerda (portas na direção Oeste/Norte/Leste)
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
