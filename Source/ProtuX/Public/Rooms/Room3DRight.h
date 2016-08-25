// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3DRight.generated.h"

/**
*	Class inherited from ARoom.
*	Class that represents a room with three doors. A room with Right orientation ( doors in the West/South/East direction).
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
