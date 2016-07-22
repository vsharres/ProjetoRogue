// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room3DRight.h"

ARoom3DRight::ARoom3DRight(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::THREE;
	RoomDirection = ERoomShape::RIGHT;
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::SOUTH);
	DoorsDirArray.Add(EDoorDirection::EAST);
}




