// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Public/Salas/CorredorLoja.h"
#include "Public/Salas/SalasGerador.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Itens/Item.h"


ACorredorLoja::ACorredorLoja(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CorredorLoja = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Corredor Loja"));
	RootComponent = CorredorLoja;

	TriggerLoja = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Trigger Loja"));
	TriggerLoja->AttachTo(RootComponent);
	Slots.AddDefaulted(3);

}

void ACorredorLoja::BeginPlay()
{
	Super::BeginPlay();

	InicializarLoja();

}

void ACorredorLoja::InicializarLoja()
{
	int32 Seed = (ASalasGerador::GetGeradorSalas(this->GetWorld()))->Seed;

	FRandomStream Stream = FRandomStream(Seed);

	for (int32 index = 0; index < Slots.Num(); index++)
	{
		int32 tipo = Stream.FRandRange(1, 100);

		if (tipo > 80)
		{
			Slots[index].Tipo = ESlotTipo::ITEM;
			Slots[index].Efeito = 0;

			UItem* itemSlot = NewObject<UItem>(this, Itens[Stream.FRandRange(0, Itens.Num() - 1)]);

			if (itemSlot)
			{
				Slots[index].Item = itemSlot;
				Slots[index].Custo = itemSlot->Custo;
				Itens.RemoveAt(Stream.FRandRange(0, Itens.Num() - 1));
			}

		}
		else if (tipo > 30)
		{
			Slots[index].Tipo = ESlotTipo::ENERGIA;
			Slots[index].Efeito = 100;
			Slots[index].Custo = 5;
		}
		else
		{
			Slots[index].Tipo = ESlotTipo::VIDA;
			Slots[index].Efeito = 100;
			Slots[index].Custo = 10;
		}


	}

	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	if (!gameMode->bNovoJogo && !gameMode->bNaoSalvar)
	{
		CarregarLoja();
	}

}

void ACorredorLoja::ComprarSlot(int32 slot, AJogador* jogador)
{
	switch (Slots[slot].Tipo)
	{
	case ESlotTipo::VIDA:
		jogador->AdicionarVida(Slots[slot].Efeito);
		break;
	case ESlotTipo::ENERGIA:
		jogador->AdicionarEnerngia(Slots[slot].Efeito);
		break;
	case ESlotTipo::ITEM:
		Slots[slot].Item->InicializarItem(jogador);
		break;
	default:
		break;
	}

	jogador->AdicionarMoedas(-Slots[slot].Custo);

	SalvarLoja();

}

void ACorredorLoja::SalvarLoja()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++)
		{
			if (Slots[index].bComprado)
			{
				SaveInst->ItensComprados[index] = true;
			}
		}

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void ACorredorLoja::CarregarLoja()
{

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++)
		{
			Slots[index].bComprado = SaveInst->ItensComprados[index];
		}
	}
}

