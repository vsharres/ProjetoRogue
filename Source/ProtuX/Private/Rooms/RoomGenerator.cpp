// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProtuX.h"
#include "RoomGenerator.h"
#include "Corridor.h"
#include "ShopCorridor.h"
#include "Room.h"
#include "Room2D.h"
#include "Room2DRight.h"
#include "Room2DLeft.h"
#include "Room3D.h"
#include "Room3DRight.h"
#include "Room3DLeft.h"
#include "Room4D.h"

ARoomGenerator::ARoomGenerator()
{
	//Initializing properties
	PrimaryActorTick.bCanEverTick = false;
	Room2DIndex = 1;
	Room3DIndex = 2;
	Room4DIndex = 3;
	Rooms.Empty();
	RoomsPositions.Empty();
	PreviousGeneratedRooms.Empty();
	bIsItemSpawned = false;
	bIsKeySpawned = false;
	bBossSpawned = false;
	bIsShopSpawned = false;
	MinNumRooms = 5;
	MaxNumRooms = 10;

	MaxLength = 100000.0f;
	MaxWidth = 100000.0f;

}

ARoomGenerator* ARoomGenerator::GetRoomGenerator(UObject* level)
{
	if (level)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(level); //Pointer to the UWorld, to find the room generator
		if (World != nullptr)
		{
			for (TActorIterator<ARoomGenerator> ActorItr(World); ActorItr; ++ActorItr) //iterating on all actors to find the room generator
			{
				if ((*ActorItr))
				{
					return *ActorItr;
				}
			}
		}
	}

	return nullptr;
}

void ARoomGenerator::InitializeGenerator(ARoom* startRoom, int32 newSeed, int32 curLevel)
{
	AProtuXGameMode* game = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	//Save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//check if a save game exist
	UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex) == false ? UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex) : NULL;
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	int32 Level;

	if (!SaveInst->bIsNewGame && SaveInst->bIsContinuingGame && !game->bNoSave) //if it is not a new game, load the rooms
	{
		LoadRooms();
		Level = SaveInst->CurrentLevel;
	}
	else
	{
		this->Seed = newSeed;
		Level = curLevel;
	}

	GeneratingStream = FRandomStream(Seed);

	SetNumRooms(Level);

	//add the starting room to the room array
	Rooms.Add(startRoom);
	Rooms.Add(NULL);

	AddToDoorArray(startRoom);

	GenerateLevel(startRoom); //Generate level

	OnLevelGenerated(); //Blueprint event to trigger the navmesh recalculations
}


FRotator ARoomGenerator::GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door)
{

	FRotator toReturn;
	FVector vec;

	switch (door)//choosing the door which will be rotated
	{
	case EDoorDirection::WEST:
		toReturn = roomDirection;
		break;
	case  EDoorDirection::NORTH:
		toReturn = FRotationMatrix(roomDirection).GetScaledAxis(EAxis::Y).Rotation();
		break;
	case EDoorDirection::EAST:
		vec = -(roomDirection.Vector());
		toReturn = vec.Rotation();
		break;
	case EDoorDirection::SOUTH:
		vec = -(FRotationMatrix(roomDirection).GetScaledAxis(EAxis::Y));
		toReturn = vec.Rotation();
		break;

	default:
		toReturn = FRotator();
		break;
	}

	return toReturn;
}

int32 ARoomGenerator::GetNumVoidDoors()
{
	int32 empty = 0;

	//Contar o número de salas nulas dentro do array de salas, sabendo assim quantas salas ainda podem ser geradas.
	//Count the number of empty rooms in the rooms array, to know how many rooms can still be generated
	for (const auto& Room : Rooms)
	{
		if (!(*Room).IsValidLowLevel())
		{
			empty++;
		}
	}

	return empty;
}

int32 ARoomGenerator::LastValidRoom()
{

	int32 index = -1;
	//Find last valid room
	for (int32 i = 0; i < Rooms.Num(); i++)
	{
		if (Rooms[i])
		{
			index = i;
		}
		else
		{
			break;
		}
	}

	return index;
}

FTransform ARoomGenerator::GenerateRoomTrans(ARoom* SalaAnterior, const FRotator DirecaoPorta)
{
	//To determine the transform of the next room, we use the direction of the door to which the room will be connected, the room offset, the previous room offset and the corridor offset
	FVector Trans = (DirecaoPorta.Vector() * (((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomOffset() + SalaAnterior->GetRoomOffset() + (1150.0f * 2))) + SalaAnterior->GetActorLocation();

	//rotate the room to face the correct door
	FVector dir = -(DirecaoPorta.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans, ((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomScale());
}

FTransform ARoomGenerator::GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection)
{
	//To determine the corridor transform, we use the direction of the door, the previous room offset and the corridor offset
	FVector Trans = (doorDirection.Vector() * (1150.0f + previousRoom->GetRoomOffset())) + previousRoom->GetActorLocation();

	//Rotate the corridor to face the door
	FVector dir = -(doorDirection.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans);
}

TSubclassOf<ARoom> ARoomGenerator::SelectRoom(ARoom* previousRoom)
{
	TSubclassOf<ARoom> toReturn;

	//min index in the rooms array
	int32 index = 0; 
	//Max index in the rooms array
	int32 limit = 0; 

	//the difference between the number of generated rooms and the total number of rooms allowed
	int32 diff = NumGeneratedRooms - Rooms.Num();

	//If the number is equals to 0, only rooms with 1 door can be generated
	if (diff == 0) 
	{
		index = 0;
		limit = 0;

	}
	else if (diff == 1)//If the difference is equals to 1, only rooms with 2 doors can be generated
	{
		index = Room2DIndex;
		limit = Room2DIndex;
	}
	else if (diff == 2) //if the difference is equals to 2, only rooms with 3 doors can be generated
	{
		index = Room3DIndex;
		limit = Room3DIndex;
	}
	else if (diff == 3) //if the difference is equals to 4, only rooms with 4 doors can be generated
	{
		index = Room4DIndex;
		limit = Room4DIndex;
	}
	else //else, any room can be generated
	{

		index = Room2DIndex;
		limit = TypesRooms.Num() - 1;

	}

	toReturn = TypesRooms[GeneratingStream.FRandRange(index, limit)]; //Choose randomly between the limits of generations

	return toReturn;
}

bool ARoomGenerator::IsCollidingToDirection(EDoorDirection direction, const FTransform& trans)
{

	ARoom* room = (ARoom*)GeneratedRoom->GetDefaultObject();

	//Get the room transform generated to test collisions
	FVector Pos = (GetRelativeDoorDirection(trans.Rotator(), direction).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + trans.GetLocation();

	bool result = InPositionArray(Pos);


	return result;
}

void ARoomGenerator::LoadRooms()
{
	//instantiate the save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Load game from slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast() && !SaveInst->bIsNewGame)
	{
		//Update the properties of the room generator
		this->Seed = SaveInst->Seed;
		this->MaxNumRooms = SaveInst->MaxNumRooms;
		this->MinNumRooms = SaveInst->MinNumRooms;
		this->LoadedRooms.Empty();
		this->LoadedRooms = SaveInst->RoomsWithEnemies;

	}
}

void ARoomGenerator::SaveRooms()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNoSave)
		return;

	//instantiate the save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //check if the save game slot already exists, if not, create a new one
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast()) 
	{
		//Update the save properties with the generator properties
		SaveInst->Seed = this->Seed;
		SaveInst->MaxNumRooms = this->MaxNumRooms;
		SaveInst->MinNumRooms = this->MinNumRooms;
		SaveInst->RoomsWithEnemies.Empty();

		for (const auto& Room : Rooms)//Update each room that have had its enemies defeated
		{
			SaveInst->RoomsWithEnemies.Add(Room->bRoomHasEnemies);
		}

		//Save rooms
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void ARoomGenerator::GenerateSpecialRoom()
{
	if (((ARoom*)GeneratedRoom->GetDefaultObject())->GetNumDoors() == ENumberDoors::ONE) //Only select special rooms in the case with 1 door rooms
	{
		int32 prob = GeneratingStream.FRandRange(0, 100); //Probability to generate a room

		if (!bIsItemSpawned &&
			(prob > 66 || GetNumVoidDoors() == 3 && Rooms.Num() == NumGeneratedRooms)) //Generate the item room
		{
			GeneratedRoom = ItemRoom;
			bIsItemSpawned = true;
			return;
		}

		if (!bIsKeySpawned &&
			(prob > 33 || GetNumVoidDoors() == 2 && Rooms.Num() == NumGeneratedRooms)) //Generate the key room
		{
			GeneratedRoom = KeyRoom;
			bIsKeySpawned = true;
			return;
		}

		if (!bBossSpawned &&
			(prob < 33 || GetNumVoidDoors() == 1 && Rooms.Num() == NumGeneratedRooms)) //Generate the boos room
		{
			GeneratedRoom = BossRoom;
			bBossSpawned = true;
			return;
		}

	}
}

bool ARoomGenerator::InPositionArray(const FVector& pos)
{
	//threshold to compare positions
	float threshold = 800.0f; 

	for (const auto& position : RoomsPositions) //check room position to all rooms inside the rooms arrays
	{
		if (FMath::Abs(pos.X - position.X) <= threshold && FMath::Abs(pos.Y - position.Y) <= threshold)
		{
			return true;
		}
		else if (pos.X > StartingRoom->GetActorLocation().X + MaxLength ||
			pos.X < StartingRoom->GetActorLocation().X - MaxLength||
			pos.Y > StartingRoom->GetActorLocation().Y + MaxWidth / 2 ||
			pos.Y < StartingRoom->GetActorLocation().Y - MaxWidth / 2)
		{
			return true;
		}
	}

	return false;
}

void ARoomGenerator::SetNumRooms(int32 currentLevel)
{
	if (MinNumRooms > MaxNumRooms)
	{
		MinNumRooms = MaxNumRooms;
	}

	NumGeneratedRooms = GeneratingStream.FRandRange(MinNumRooms, MaxNumRooms) + (currentLevel * 2); //increase the total number of rooms multiplying by the current level

}

void ARoomGenerator::AddToDoorArray(ARoom* room)
{
	ENumberDoors numDoors = room->GetNumDoors(); //Get all doors in a room and add it to the doors array

	switch (numDoors) //set the doors array using the number of doors
	{
	case ENumberDoors::ONE:
		RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
		break;
	case ENumberDoors::TWO:

		switch (room->GetRoomShape()) // for each room type there is a different array of doors, the order in the array is used to get the correct room direction
		{
		case ERoomShape::Default:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::EAST).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		case  ERoomShape::LEFT:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::NORTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		case ERoomShape::RIGHT:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::SOUTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		}
		break;

	case ENumberDoors::THREE:
		switch (room->GetRoomShape())
		{
		case ERoomShape::Default:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::SOUTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::NORTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		case  ERoomShape::LEFT:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::NORTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::EAST).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		case ERoomShape::RIGHT:
			RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::SOUTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::EAST).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
			break;
		}
		break;

	case ENumberDoors::FOUR:
		RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
		RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::NORTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
		RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::EAST).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
		RoomsPositions.Add((GetRelativeDoorDirection(room->GetActorRotation(), EDoorDirection::SOUTH).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + room->GetActorLocation());
		break;

	}
}

void ARoomGenerator::GenerateLevel_Implementation(ARoom* currentRoom)
{
	currentRoom->bVisited = true; //set current room to be visited

	for (int32 i = currentRoom->ConectedRooms.Num() + 1; i <= (int32)currentRoom->GetNumDoors(); i++) //loop to all generated rooms
	{
		if (currentRoom->ConectedRooms.Num() <= (int32)currentRoom->GetNumDoors())
		{
			//generate a new room connected to the current room
			ARoom* room = GenerateRoom(currentRoom, GetRelativeDoorDirection(currentRoom->GetActorRotation(), (currentRoom->GetArrayDoors())[i - 1]));

			if (!room->bVisited) //if the room was not visited yet, recursively call the function to generate the next room
			{
				GenerateLevel(room);
			}
		}
	}
}


ARoom* ARoomGenerator::GenerateRoom(ARoom* previousRoom, const FRotator& doorDirection)
{
	GeneratedRoom = NULL;

	GeneratedRoom = SelectRoom(previousRoom); //Select the type of room to be generates

	GenerateSpecialRoom(); //check if the selected room will chage to a special room

	FTransform roomTrans = GenerateRoomTrans(previousRoom, doorDirection); //Generate the transform of the new room

	CheckColision(roomTrans, doorDirection); //check the room for collision, the type of room can change if there is collisions with other rooms

	//Spawn new room
	ARoom* newRoom = GetWorld()->SpawnActor<ARoom>(GeneratedRoom, roomTrans.GetLocation(), roomTrans.GetRotation().Rotator());

	if (newRoom->IsValidLowLevelFast())
	{
		newRoom->SetActorScale3D(newRoom->GetRoomScale()); //set correct scale
		newRoom->ConectedRooms.Add(previousRoom); //Connect the new room to previous room
		previousRoom->ConectedRooms.Add(newRoom);
		PreviousGeneratedRooms.Add(GeneratedRoom);

	}

	GenerateCorridor(previousRoom, doorDirection); //Generate the corridor between rooms

	//if the new room has more than 1 door, add to the rooms array the number of rooms that we already know we have to generate to guarantee that there will be no doors connected to nowhere.
	if (newRoom->GetNumDoors() > ENumberDoors::ONE)
	{
		Rooms.AddZeroed((int32)newRoom->GetNumDoors() - 1);
	}

	Rooms[LastValidRoom() + 1] = newRoom; //new room is the last valid room

	AddToDoorArray(newRoom); //Add doors from the new room to the doors array

	if (LoadedRooms.Num() >= Rooms.Num()) //Check if the room is being loaded or is from a new level
	{
		newRoom->bRoomHasEnemies = LoadedRooms[Rooms.Find(newRoom)]; //find the room in the loaded rooms array

		if (newRoom->bRoomHasEnemies)
		{
			newRoom->DeactivateTrigger(); //update the enemies state in the room
		}
		
	}

	newRoom->SpawnEnemies(GeneratingStream); //spawn enemies in the rooms

	UE_LOG(LogTemp, Warning, TEXT(" Room nome: %s numero: %d"), *newRoom->GetName(), Rooms.Num());

	return newRoom;
}

void ARoomGenerator::GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection)
{

	FTransform CorridorTrans = GenerateCorridorTrans(previousRoom, doorDirection); //Generate the corridor transform

	int32 value = GeneratingStream.FRandRange(0, 100); //Probability to generate a type of room

	//guarantee that the shop will be generated
	if ((value >= 70 && !bIsShopSpawned) ||
		(!bIsShopSpawned && ((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomType() == ERoomType::BOSS))
	{
		AShopCorridor* newCorridor = GetWorld()->SpawnActor<AShopCorridor>(ShopCorridor, CorridorTrans.GetLocation(), CorridorTrans.GetRotation().Rotator());
		newCorridor->SetActorScale3D(newCorridor->GetScale());
		bIsShopSpawned = true;
	}
	else
	{
		//Spawn of a normal corridor
		ACorridor* newCorridor = GetWorld()->SpawnActor<ACorridor>(CorridorTypes[GeneratingStream.FRandRange(0, CorridorTypes.Num() - 1)], CorridorTrans.GetLocation(), CorridorTrans.GetRotation().Rotator());
		newCorridor->SetActorScale3D(newCorridor->GetScale());
	}



}

void ARoomGenerator::CheckColision(const FTransform& trans, const FRotator& doorDirection)
{
	bool isColliding = false;

	//Check each doors direction in the room for collision, if there is a collision, change the type of room to a type that has no collision
	do
	{
		ARoom* room = (ARoom*)GeneratedRoom->GetDefaultObject();
		ENumberDoors numDoors = room->GetNumDoors();

		switch (numDoors) 
		{
		case ENumberDoors::TWO:

			switch (room->GetRoomShape())
			{
			case ERoomShape::Default:
				isColliding = false;
				if (IsCollidingToDirection(EDoorDirection::EAST, trans))
				{
					GeneratedRoom = TypesRooms[0];
					isColliding = true;
				}
				break;
			case  ERoomShape::LEFT:
				isColliding = false;
				if (IsCollidingToDirection(EDoorDirection::NORTH, trans))
				{
					GeneratedRoom = TypesRooms[1];
					isColliding = true;
				}
				break;
			case ERoomShape::RIGHT:
				isColliding = false;
				if (IsCollidingToDirection(EDoorDirection::SOUTH, trans))
				{
					GeneratedRoom = TypesRooms[2];
					isColliding = true;
				}
				break;
			}

			break;
		case ENumberDoors::THREE:
			isColliding = false;

			for (int32 i = 1; i <= 2; i++)
			{
				if (IsCollidingToDirection(room->GetArrayDoors()[i], trans))
				{
					switch (room->GetRoomShape())
					{
					case ERoomShape::Default:
						GeneratedRoom = TypesRooms[3];
						break;
					case ERoomShape::LEFT:
						GeneratedRoom = TypesRooms[5];
						break;
					case ERoomShape::RIGHT:
						GeneratedRoom = TypesRooms[4];
						break;
					}

					isColliding = true;
					break;
				}
			}
			break;
		case ENumberDoors::FOUR:
			isColliding = false;

			for (int32 i = 1; i <= 3; i++)
			{
				if (IsCollidingToDirection(room->GetArrayDoors()[i], trans))
				{
					GeneratedRoom = TypesRooms[6];
					isColliding = true;
					break;
				}
			}
			break;
		default:
			isColliding = false;
			break;
		}

	} while (isColliding);

}

