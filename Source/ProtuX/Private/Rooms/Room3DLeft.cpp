// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room3DLeft.h"

ARoom3DLeft::ARoom3DLeft(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//initializing properties
	NumberDoors = ENumberDoors::THREE;
	RoomDirection = ERoomShape::LEFT;
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::NORTH);
	DoorsDirArray.Add(EDoorDirection::EAST);
}

