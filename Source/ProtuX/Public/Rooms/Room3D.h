// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room3D.generated.h"


/**
*	Class inherited from ARoom.
*	Class that represents a room with three doors. A room with Default orientation ( doors in the West/South/North direction).
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
