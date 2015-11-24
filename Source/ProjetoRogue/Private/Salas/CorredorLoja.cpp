// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Public/Salas/CorredorLoja.h"
#include "Public/Salas/SalasGerador.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Itens/Item.h"


ACorredorLoja::ACorredorLoja(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades.
	CorredorLoja = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Corredor Loja"));
	RootComponent = CorredorLoja;

	TriggerLoja = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Trigger Loja"));
	TriggerLoja->AttachTo(RootComponent);

	//Inicializando os slots da loja.
	Slots.AddDefaulted(3);

}

void ACorredorLoja::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização.

	InicializarLoja();

}

void ACorredorLoja::InicializarLoja()
{

	FRandomStream Stream = (ASalasGerador::GetGeradorSalas(this->GetWorld()))->StreamGeracao; //Stream de geração para os slots.

	for (int32 index = 0; index < Slots.Num(); index++)//definindo os itens que estaram em cada slot, sendo que sempre um dos slots é o slot do item.
	{

		if (index == 2)
		{
			Slots[index].Tipo = ESlotTipo::ITEM;
			Slots[index].Efeito = 0;
			
			//Item a ser gerado para o slot.
			UItem* itemSlot = NewObject<UItem>(this, Itens[Stream.FRandRange(0, Itens.Num() - 1)]);

			if (itemSlot)
			{
				//Definindo propriedades dos slots.
				Slots[index].Item = itemSlot;
				Slots[index].Custo = itemSlot->Custo; 
				Itens.RemoveAt(Stream.FRandRange(0, Itens.Num() - 1));
			}

		}
		else if (index == 1)//criando o slot com o pack de energia
		{
			Slots[index].Tipo = ESlotTipo::ENERGIA;
			Slots[index].Efeito = 100;
			Slots[index].Custo = 5;
		}
		else //criando o slot com o pack de vida
		{
			Slots[index].Tipo = ESlotTipo::VIDA;
			Slots[index].Efeito = 100;
			Slots[index].Custo = 10;
		}


	}

	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	//Criar o objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (!SaveInst->bNovoJogo && !gameMode->bNaoSalvar && SaveInst->bContinuarJogo) //para o caso de o jogo estar sendo carregado de um save.
	{
		CarregarLoja();
	}

}

void ACorredorLoja::ComprarSlot(int32 slot, AJogador* jogador)
{
	switch (Slots[slot].Tipo) //Dependendo do tipo do slot
	{
	case ESlotTipo::VIDA:
		jogador->AdicionarVida(Slots[slot].Efeito); //adicionar vida ao jogador
		break;
	case ESlotTipo::ENERGIA:
		jogador->AdicionarEnerngia(Slots[slot].Efeito); //adicionar energia ao jogador
		break;
	case ESlotTipo::ITEM:
		Slots[slot].Item->InicializarItem(jogador); //Incializar o item ao jogador.
		break;
	default:
		break;
	}

	jogador->AdicionarMoedas(-Slots[slot].Custo); //Remover moedas de acordo com o preço do slot.

	SalvarLoja();

}

void ACorredorLoja::SalvarLoja()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNaoSalvar)
		return;

	//Criar o objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Salvar os slots que foram comprados.
		{
			if (Slots[index].bComprado)
			{
				SaveInst->ItensComprados[index] = true;
			}
		}
		
		//salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void ACorredorLoja::CarregarLoja()
{
	//Criar o objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		for (int32 index = 0; index < Slots.Num(); index++) //Carregar os slots comprados
		{
			Slots[index].bComprado = SaveInst->ItensComprados[index];
		}
	}
}

