// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ShopCorridor.h"
#include "RoomGenerator.h"
#include "ProtuXPlayer.h"
#include "Item.h"


AShopCorridor::AShopCorridor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	ShopCorridorRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Corredor Loja"));
	RootComponent = ShopCorridorRoot;

	ShopTrigger = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Trigger Loja"));
	ShopTrigger->SetupAttachment(RootComponent,"ShopTrigger");

	//Defaulting slots
	Slots.AddDefaulted(3);

}

void AShopCorridor::BeginPlay()
{
	Super::BeginPlay(); 

	InitializeShop();
}

void AShopCorridor::InitializeShop()
{
	//Random stream generator for the slots
	FRandomStream Stream = (ARoomGenerator::GetRoomGenerator(this->GetWorld()))->GeneratingStream;

	//Defining each slot in the shop
	for (int32 index = 0; index < Slots.Num(); index++)
	{
		if (index == 2)
		{
			Slots[index].Type = ESlotType::ITEM;
			Slots[index].Effect = 0;
			
			//Generated item slot
			UItem* itemSlot = NewObject<UItem>(this, Items[Stream.FRandRange(0, Items.Num() - 1)]);

			if (itemSlot)
			{
				//Defining the slot properties
				Slots[index].Item = itemSlot;
				Slots[index].Cost = itemSlot->Cost; 
				Items.RemoveAt(Stream.FRandRange(0, Items.Num() - 1));
			}

		}
		else if (index == 1)//Generating the energy slot
		{
			Slots[index].Type = ESlotType::ENERGY;
			Slots[index].Effect = 100;
			Slots[index].Cost = 5;
		}
		else //Generating the health slot
		{
			Slots[index].Type = ESlotType::HEALTH;
			Slots[index].Effect = 100;
			Slots[index].Cost = 10;
		}


	}

	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	//Instantiate the save object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Load game slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (!SaveInst->bIsNewGame && !gameMode->bNoSave && SaveInst->bIsContinuingGame) //only load shop if the player is continuing a game
	{
		LoadShopState();
	}

}

void AShopCorridor::BuySlot(int32 slot, AProtuXPlayer* player)
{
	switch (Slots[slot].Type)
	{
	case ESlotType::HEALTH:
		player->AddHealth(Slots[slot].Effect); 
		break;
	case ESlotType::ENERGY:
		player->AddEnergy(Slots[slot].Effect); 
		break;
	case ESlotType::ITEM:
		Slots[slot].Item->InitializeItem(player); 
		break;
	default:
		break;
	}

	player->AddCoins(-Slots[slot].Cost);

	SaveShopState();

}

void AShopCorridor::SaveShopState()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNoSave)
		return;

	//Instantiate the save object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Load game slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Save the slots
		{
			if (Slots[index].bBought)
			{
				SaveInst->ItemsBought[index] = true;
			}
		}
		
		//Save game
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AShopCorridor::LoadShopState()
{
	//Instantiate the save object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Load game slot
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Load shop
		{
			Slots[index].bBought = SaveInst->ItemsBought[index];
		}
	}
}

