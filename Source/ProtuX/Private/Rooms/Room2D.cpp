// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room2D.h"

ARoom2D::ARoom2D(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::TWO;
	RoomDirection = ERoomShape::STANDARD;
	ConectedRooms.Empty();
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::EAST);
	bVisited = false;

}
