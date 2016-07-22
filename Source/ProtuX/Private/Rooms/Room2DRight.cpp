// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room2DRight.h"

ARoom2DRight::ARoom2DRight(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::TWO;
	RoomDirection = ERoomShape::RIGHT;
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::SOUTH);
}


