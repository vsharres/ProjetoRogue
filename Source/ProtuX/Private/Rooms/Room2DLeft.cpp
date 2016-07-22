// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Room2DLeft.h"

ARoom2DLeft::ARoom2DLeft(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicizalizando as propriedades.
	NumberDoors = ENumberDoors::TWO;
	RoomDirection = ERoomShape::LEFT;
	DoorsDirArray.Empty();
	DoorsDirArray.Add(EDoorDirection::WEST);
	DoorsDirArray.Add(EDoorDirection::NORTH);

}




