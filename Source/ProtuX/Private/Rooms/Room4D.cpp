// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room4D.h"

ARoom4D::ARoom4D(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::FOUR;
	RoomDirection = ERoomShape::Default;
	ConectedRooms.Empty();
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::NORTH);
	DoorsDirArray.Add(EDoorDirection::EAST);
	DoorsDirArray.Add(EDoorDirection::SOUTH);
	bVisited = false;
}

