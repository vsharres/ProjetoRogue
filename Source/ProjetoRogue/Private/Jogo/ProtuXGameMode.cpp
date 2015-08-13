// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Public/Jogo/ProtuXGameMode.h"


AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	bNovoJogo = true;
}


void AProtuXGameMode::LoadProfile()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		bNovoJogo = SaveInst->bNovoJogo;

		if (bNovoJogo)
		{
			NumJogos = SaveInst->NumJogos;

			SaveInst->NumJogos++;
			UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

			
		}

		NumJogos = SaveInst->NumJogos;
		
	}
}

void AProtuXGameMode::ContinuarJogo()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bNovoJogo = false;
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

