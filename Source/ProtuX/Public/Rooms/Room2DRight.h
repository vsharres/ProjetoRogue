// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2DRight.generated.h"

/*
*	Class inherited from ARoom.
*	Class that represents a room with two doors. A room with Right orientation ( doors in the West/South direction).
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
