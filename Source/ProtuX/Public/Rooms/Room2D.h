// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room2D.generated.h"


/*
*	Class inherited from ARoom.
*	Class that represents a room with two doors. A room with standard orientation ( doors in the West/East direction).
*/
UCLASS()
class PROTUX_API ARoom2D : public ARoom
{
	GENERATED_BODY()

#pragma region Constructor
public:

	// Standard Constructor.
	ARoom2D(const FObjectInitializer& ObjectInitializer);
#pragma endregion Constructor


};
