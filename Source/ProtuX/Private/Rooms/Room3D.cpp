// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room3D.h"


ARoom3D::ARoom3D(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::THREE;
	RoomDirection = ERoomShape::STANDARD;
	ConectedRooms.Empty();
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::SOUTH);
	DoorsDirArray.Add(EDoorDirection::NORTH);
	bVisited = false;
}

