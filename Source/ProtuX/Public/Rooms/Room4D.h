// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room4D.generated.h"

/*
*	Classe que representa uma sala com quatro portas. Sala orientada com a orienta��o padr�o (portas na dire��o Oeste/Norte/Leste/Sul)
*/
UCLASS()
class PROTUX_API ARoom4D : public ARoom
{
	GENERATED_BODY()
#pragma region Constructor

public:
	//Constructor
	ARoom4D(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

};
