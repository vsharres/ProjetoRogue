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

	SaveInst->NumJogos++;
	UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		bNovoJogo = SaveInst->bNovoJogo;
		NumJogos = SaveInst->NumJogos;
	}
}

