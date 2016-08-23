// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3DLeft.generated.h"

/*
*	Class inherited from ARoom.
*	Class that represents a room with three doors. A room with Left orientation ( doors in the West/North/East direction).
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
