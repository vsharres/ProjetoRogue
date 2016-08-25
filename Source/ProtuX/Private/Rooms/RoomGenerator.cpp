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
	//Inicizalizando as propriedades.
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
		UWorld* World = GEngine->GetWorldFromContextObject(level); //Ponteiro ao UWorld atual, para encontrar o gerador de salas.
		if (World != nullptr)
		{
			for (TActorIterator<ARoomGenerator> ActorItr(World); ActorItr; ++ActorItr) //Iterando sobre todos os atores até encontrar o gerador de salas.
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

	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex) == false ? UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex) : NULL;
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	int32 Level;

	if (!SaveInst->bIsNewGame && SaveInst->bIsContinuingGame && !game->bNoSave) //Se não for um novo jogo, fazer o load das salas.
	{
		LoadRooms();
		Level = SaveInst->CurrentLevel;
	}
	else
	{
		this->Seed = newSeed;
		Level = curLevel;
	}

	GeneratingStream = FRandomStream(Seed); //Inicializando o stream randomico com o novo seed.

	SetNumRooms(Level); //Set do num de salas a ser gerado.

	//Adicionando a sala inicial ao array de salas.
	Rooms.Add(startRoom);
	Rooms.Add(NULL);

	AddToDoorArray(startRoom);

	GenerateLevel(startRoom); //Gerar o level em si

	OnLevelGenerated(); //Evento para o blueprint.
}


FRotator ARoomGenerator::GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door)
{

	FRotator toReturn;
	FVector vec;

	switch (door) //escolhendo qual porta terá a sua rotação retornada.
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
	//Encontrar a última sala válida.
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
	//Para determinar o transform da proxima sala, usamos a direção da porta que vai estar conecatada a sala, o offset da sala a ser gerada, o offset da sala anterior e o offset do corredor.
	FVector Trans = (DirecaoPorta.Vector() * (((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomOffset() + SalaAnterior->GetRoomOffset() + (1150.0f * 2))) + SalaAnterior->GetActorLocation();

	//Rodar a sala para ficar virada a porta.
	FVector dir = -(DirecaoPorta.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans, ((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomScale());
}

FTransform ARoomGenerator::GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection)
{
	//Parar determinar o transform do corredor, usamos a direção da porta com o offset da sala anterior e o offset do corredor em si.
	FVector Trans = (doorDirection.Vector() * (1150.0f + previousRoom->GetRoomOffset())) + previousRoom->GetActorLocation();

	//Rodar o corredor para ficar virada a porta.
	FVector dir = -(doorDirection.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans);
}

TSubclassOf<ARoom> ARoomGenerator::SelectRoom(ARoom* previousRoom)
{
	TSubclassOf<ARoom> toReturn; //Room a ser selecionada

	int32 index = 0; //Indice mínimo dentro do array de salas.
	int32 limit = 0; //Indice máximo dentro do array de salas.

	int32 diff = NumGeneratedRooms - Rooms.Num(); //Saber a diferença entre o número de salas já geradas e o quantas ainda devem ser.

	if (diff == 0) //Se o número é igual, apenas a sala com 1 porta pode ser gerada.
	{
		index = 0;
		limit = 0;

	}
	else if (diff == 1) //Se a diferença é igual a 1, apenas a sala com 2 portas pode ser gerada.
	{
		index = Room2DIndex;
		limit = Room2DIndex;
	}
	else if (diff == 2) //Se a diferença é igual a 2, apenas a sala com 3 portas pode ser gerada.
	{
		index = Room3DIndex;
		limit = Room3DIndex;
	}
	else if (diff == 3) //Se a diferença é igual a 4, apenas a sala com 4 portas pode ser gerada.
	{
		index = Room4DIndex;
		limit = Room4DIndex;
	}
	else //Caso contrario, qualquer sala que tenha mais de 1 porta pode ser gerada.
	{

		index = Room2DIndex;
		limit = TypesRooms.Num() - 1;

	}

	toReturn = TypesRooms[GeneratingStream.FRandRange(index, limit)]; //Escolher randomicamente dentre as salas que podem ser escolhidas.

	return toReturn;
}

bool ARoomGenerator::IsCollidingToDirection(EDoorDirection direction, const FTransform& trans)
{

	ARoom* room = (ARoom*)GeneratedRoom->GetDefaultObject();
	FVector Pos = (GetRelativeDoorDirection(trans.Rotator(), direction).Vector() * (room->GetRoomOffset() + (1150.0f * 2) + 1748.0f)) + trans.GetLocation(); //Get o transformo da sala que vai ser gerada para testar colisao.

	bool result = InPositionArray(Pos);


	return result;
}

void ARoomGenerator::LoadRooms()
{
	//Criar o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast() && !SaveInst->bIsNewGame) //Checar validade de ponteiro.
	{
		//Atualizar as propriedadas do gerador com as do save.
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

	//Criar o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //Checar se o savegame já existe, e caso não, criar um novo.
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast()) //Checar validade de ponteiro.
	{
		//Atulizar as propriedades do save com as propriedades do gerador.
		SaveInst->Seed = this->Seed;
		SaveInst->MaxNumRooms = this->MaxNumRooms;
		SaveInst->MinNumRooms = this->MinNumRooms;
		SaveInst->RoomsWithEnemies.Empty();

		for (const auto& Room : Rooms) //Atulizar cada sala que teve os seus inimigos já derrotados
		{
			SaveInst->RoomsWithEnemies.Add(Room->bRoomHasEnemies);
		}

		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void ARoomGenerator::GenerateSpecialRoom()
{
	if (((ARoom*)GeneratedRoom->GetDefaultObject())->GetNumDoors() == ENumberDoors::ONE) //Apenas selecionar salas especiais para o caso de salas com 1 porta.
	{

		int32 prob = GeneratingStream.FRandRange(0, 100); //Probablidade de gerar um tipo de sala.

		if (!bIsItemSpawned &&
			(prob > 66 || GetNumVoidDoors() == 3 && Rooms.Num() == NumGeneratedRooms)) //Gerar sala do item
		{
			GeneratedRoom = ItemRoom;
			bIsItemSpawned = true;
			return;
		}

		if (!bIsKeySpawned &&
			(prob > 33 || GetNumVoidDoors() == 2 && Rooms.Num() == NumGeneratedRooms)) //Gerar sala da chave
		{
			GeneratedRoom = KeyRoom;
			bIsKeySpawned = true;
			return;
		}

		if (!bBossSpawned &&
			(prob < 33 || GetNumVoidDoors() == 1 && Rooms.Num() == NumGeneratedRooms)) //Gerar sala do boss.
		{
			GeneratedRoom = BossRoom;
			bBossSpawned = true;
			return;
		}

	}
}

bool ARoomGenerator::InPositionArray(const FVector& pos)
{
	float threshold = 800.0f; //Tolerancia para comparar as posições

	for (const auto& position : RoomsPositions) //Comparar a pos com todas as salas dentro do array.
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

	NumGeneratedRooms = GeneratingStream.FRandRange(MinNumRooms, MaxNumRooms) + (currentLevel * 2); //Aumentar o número de salas de acordo com o level atual.

}

void ARoomGenerator::AddToDoorArray(ARoom* room)
{
	ENumberDoors numDoors = room->GetNumDoors(); //Pegar o numero de portas e adicionar ao array de portas da sala.

	switch (numDoors) //Para cada número de portas o padro de portas é diferente.
	{
	case ENumberDoors::ONE:
		RoomsPositions.Contains<FVector>(room->GetActorLocation()) == false ? RoomsPositions.Add(room->GetActorLocation()) : NULL;
		break;
	case ENumberDoors::TWO:

		switch (room->GetRoomShape()) //Cada tipo de sala de um determinado número de portas tem um padrão diferente de direção das portas.
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
	currentRoom->bVisited = true; //Room atual foi visitada

	for (int32 i = currentRoom->ConectedRooms.Num() + 1; i <= (int32)currentRoom->GetNumDoors(); i++) //Loop em todas as salas geradas.
	{
		if (currentRoom->ConectedRooms.Num() <= (int32)currentRoom->GetNumDoors())
		{
			ARoom* room = GenerateRoom(currentRoom, GetRelativeDoorDirection(currentRoom->GetActorRotation(), (currentRoom->GetArrayDoors())[i - 1])); //Gerar uma nova sala conectada a sala atual numa determinada porta.

			if (!room->bVisited) //Se a sala gerada não foi visitada, recursivamente gerar uma nova sala.
			{
				GenerateLevel(room);
			}
		}
	}
}


ARoom* ARoomGenerator::GenerateRoom(ARoom* previousRoom, const FRotator& doorDirection)
{
	GeneratedRoom = NULL;

	GeneratedRoom = SelectRoom(previousRoom); //Selecionar sala a ser gerada.

	GenerateSpecialRoom(); //Checar se a sala pode ser transformada numa sala especial.

	FTransform roomTrans = GenerateRoomTrans(previousRoom, doorDirection); //Gerar o transform da nova sala.

	CheckColision(roomTrans, doorDirection); //Mudar o tipo da sala se a sala a ser gerada colide com alguma sala já existente.

	//Spawn da nova sala.
	ARoom* newRoom = GetWorld()->SpawnActor<ARoom>(GeneratedRoom, roomTrans.GetLocation(), roomTrans.GetRotation().Rotator());

	if (newRoom->IsValidLowLevelFast())
	{
		newRoom->SetActorScale3D(newRoom->GetRoomScale()); //Mudar escala da sala.
		newRoom->ConectedRooms.Add(previousRoom); //Conectar a sala gerada a sala anterior.
		previousRoom->ConectedRooms.Add(newRoom);
		PreviousGeneratedRooms.Add(GeneratedRoom);

	}

	GenerateCorridor(previousRoom, doorDirection); //Gerar o corredor que conecta as salas.

	if (newRoom->GetNumDoors() > ENumberDoors::ONE) //Se a sala gerada tem mais de 1 porta, adicionar ao array de salas o número necessários de espaços para as salas que serão conectadas a sala gerada. ( por exemplo uma sala de 4 portas precisa da sala anterior e mais 3 salas para serem conectadas)
	{
		Rooms.AddZeroed((int32)newRoom->GetNumDoors() - 1);
	}

	Rooms[LastValidRoom() + 1] = newRoom; //Nova sala é a ultima sala gerada.

	AddToDoorArray(newRoom); //Adicionar a nova sala ao array de portas.

	if (LoadedRooms.Num() >= Rooms.Num()) //Checar se o level foi carregado ou se é um novo level.
	{
		newRoom->bRoomHasEnemies = LoadedRooms[Rooms.Find(newRoom)]; //Atulizar o estado dos inimigos.

		if (newRoom->bRoomHasEnemies)
		{
			newRoom->DeactivateTrigger();
		}
		
	}

	newRoom->SpawnEnemies(GeneratingStream); //Fazer o spawn dos inimigos na sala.

	UE_LOG(LogTemp, Warning, TEXT(" Room nome: %s numero: %d"), *newRoom->GetName(), Rooms.Num());

	return newRoom;
}

void ARoomGenerator::GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection)
{

	FTransform CorridorTrans = GenerateCorridorTrans(previousRoom, doorDirection); //Gerar o transform do corredor.

	int32 value = GeneratingStream.FRandRange(0, 100); //Probablidade de gerar o corredor com a loja

	//Se a probablidade for alta, e a loja ainda nao foi gerada, ou se a última sala gerada foi a do boss, fazer o spawn da loja
	if ((value >= 70 && !bIsShopSpawned) ||
		(!bIsShopSpawned && ((ARoom*)GeneratedRoom->GetDefaultObject(true))->GetRoomType() == ERoomType::BOSS))
	{
		AShopCorridor* newCorridor = GetWorld()->SpawnActor<AShopCorridor>(ShopCorridor, CorridorTrans.GetLocation(), CorridorTrans.GetRotation().Rotator());
		newCorridor->SetActorScale3D(newCorridor->GetScale());
		bIsShopSpawned = true;
	}
	else
	{
		//Spawn do corredor normal.
		ACorridor* newCorridor = GetWorld()->SpawnActor<ACorridor>(CorridorTypes[GeneratingStream.FRandRange(0, CorridorTypes.Num() - 1)], CorridorTrans.GetLocation(), CorridorTrans.GetRotation().Rotator());
		newCorridor->SetActorScale3D(newCorridor->GetScale());
	}



}

void ARoomGenerator::CheckColision(const FTransform& trans, const FRotator& doorDirection)
{
	bool isColliding = false;

	do //Checar cada direcao das salas para colisao, e caso colide, mudar o tipo de sala até encontrar um tipo de sala que não colida.
	{
		ARoom* room = (ARoom*)GeneratedRoom->GetDefaultObject();
		ENumberDoors numDoors = room->GetNumDoors();

		switch (numDoors) //Para o número de portas da sala, um tipo de direcao difernte deve ser checado.
		{
		case ENumberDoors::TWO:

			switch (room->GetRoomShape()) //Checar para cada direcao e alterar a sala a ser gerada caso alguma colisao seja detectada.
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

