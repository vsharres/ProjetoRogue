// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "Room4D.generated.h"

/**
*	Class inherited from ARoom.
*	Class that represents a room with four doors. A room with Default orientation ( doors in the West/North/East/South direction).
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
