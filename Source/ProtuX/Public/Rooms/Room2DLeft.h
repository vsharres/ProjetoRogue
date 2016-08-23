// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2DLeft.generated.h"

/*
*	Class inherited from ARoom.
*	Class that represents a room with two doors. A room with Left orientation ( doors in the West/North direction).
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

