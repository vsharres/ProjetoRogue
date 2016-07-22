// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ShopCorridor.h"
#include "RoomGenerator.h"
#include "ProtuXPlayer.h"
#include "Item.h"


AShopCorridor::AShopCorridor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades.
	ShopCorridorRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Corredor Loja"));
	RootComponent = ShopCorridorRoot;

	ShopTrigger = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Trigger Loja"));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	ShopTrigger->AttachToComponent(RootComponent,Rules);

	//Inicializando os slots da loja.
	Slots.AddDefaulted(3);

}

void AShopCorridor::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização.

	InitializeShop();

}

void AShopCorridor::InitializeShop()
{

	FRandomStream Stream = (ARoomGenerator::GetRoomGenerator(this->GetWorld()))->GeneratingStream; //Stream de geração para os slots.

	for (int32 index = 0; index < Slots.Num(); index++)//definindo os Items que estaram em cada slot, sendo que sempre um dos slots é o slot do item.
	{

		if (index == 2)
		{
			Slots[index].Type = ESlotType::ITEM;
			Slots[index].Effect = 0;
			
			//Item a ser gerado para o slot.
			UItem* itemSlot = NewObject<UItem>(this, Items[Stream.FRandRange(0, Items.Num() - 1)]);

			if (itemSlot)
			{
				//Definindo propriedades dos slots.
				Slots[index].Item = itemSlot;
				Slots[index].Cost = itemSlot->Cost; 
				Items.RemoveAt(Stream.FRandRange(0, Items.Num() - 1));
			}

		}
		else if (index == 1)//criando o slot com o pack de energia
		{
			Slots[index].Type = ESlotType::ENERGY;
			Slots[index].Effect = 100;
			Slots[index].Cost = 5;
		}
		else //criando o slot com o pack de vida
		{
			Slots[index].Type = ESlotType::HEALTH;
			Slots[index].Effect = 100;
			Slots[index].Cost = 10;
		}


	}

	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	//Criar o objeto de save
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (!SaveInst->bIsNewGame && !gameMode->bNoSave && SaveInst->bIsContinuingGame) //para o caso de o jogo estar sendo carregado de um save.
	{
		LoadShopState();
	}

}

void AShopCorridor::BuySlot(int32 slot, AProtuXPlayer* player)
{
	switch (Slots[slot].Type) //Dependendo do tipo do slot
	{
	case ESlotType::HEALTH:
		player->AddHelath(Slots[slot].Effect); //adicionar vida ao jogador
		break;
	case ESlotType::ENERGY:
		player->AddEnergy(Slots[slot].Effect); //adicionar energia ao jogador
		break;
	case ESlotType::ITEM:
		Slots[slot].Item->InitializeItem(player); //Incializar o item ao jogador.
		break;
	default:
		break;
	}

	player->AddCoins(-Slots[slot].Cost); //Remover moedas de acordo com o preço do slot.

	SaveShopState();

}

void AShopCorridor::SaveShopState()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNoSave)
		return;

	//Criar o objeto de save
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Salvar os slots que foram comprados.
		{
			if (Slots[index].bBought)
			{
				SaveInst->ItemsBought[index] = true;
			}
		}
		
		//salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AShopCorridor::LoadShopState()
{
	//Criar o objeto de save
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Carregar os slots comprados
		{
			Slots[index].bBought = SaveInst->ItemsBought[index];
		}
	}
}

