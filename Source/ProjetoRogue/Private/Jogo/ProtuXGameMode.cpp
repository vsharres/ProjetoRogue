// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "InimigosControlador.h"
#include "ProtuXGameMode.h"


AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	bNovoJogo = true;
	bTutorialAtivado = true;
	bNaoSalvar = false;
	LevelAtual = 0;

}


EJogoEstado AProtuXGameMode::GetEstadoJogo() const
{
	return Estado;
}

void AProtuXGameMode::SetEstadoJogo(EJogoEstado NovoEstado)
{
	Estado = NovoEstado;

	AtualizarEstado(NovoEstado);
}

void AProtuXGameMode::AtualizarEstado(EJogoEstado NovoEstado)
{
	APlayerController* controlador;
	TArray<AActor*> InimigosControladores;

	switch (NovoEstado)
	{

	case EJogoEstado::MENUPRINCIPAL:
		UGameplayStatics::OpenLevel(this, TEXT("MenuPrincipal"), true);
		break;
	case EJogoEstado::NOVOJOGO:
		LoadNovoJogo();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), true);
		break;
	case EJogoEstado::PROXIMAFASE:
		LoadProximaFase();
		UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), true);
		break;
	case EJogoEstado::GAMEOVER:

		UGameplayStatics::GetAllActorsOfClass(this, AInimigosControlador::StaticClass(), InimigosControladores);

		for (auto Actor : InimigosControladores)
		{
			AInimigosControlador* inimgControlador = Cast<AInimigosControlador>(Actor);

			if (inimgControlador->IsValidLowLevelFast())
			{
				inimgControlador->DesativarInimigo();
			}
		}

		controlador = UGameplayStatics::GetPlayerController(this, 0);

		if (controlador->IsValidLowLevelFast())
		{
			controlador->SetCinematicMode(true, true, true);
			controlador->bShowMouseCursor = true;
		}
		break;
	case  EJogoEstado::REINICIAR:
		LoadNovoJogo();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), true);
		break;
	default:
		break;
	}
}

void AProtuXGameMode::BeginPlay()
{
	Super::BeginPlay();

	Estado = EJogoEstado::MENUPRINCIPAL;
}

void AProtuXGameMode::LoadNovoJogo()
{
	if (bNaoSalvar)
		return;

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex))
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{

		SaveInst->bNovoJogo = true;
		bNovoJogo = SaveInst->bNovoJogo;

		if (bNovoJogo)
		{
			SaveInst->NumJogos += 1;
		}

		NumJogos = SaveInst->NumJogos;

		if (NumJogos > 1)
		{
			bTutorialAtivado = false;
		}

		SaveInst->LevelAtual = 1;
		LevelAtual = SaveInst->LevelAtual;

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

	}
}

void AProtuXGameMode::LoadContinuarJogo()
{
	if (bNaoSalvar)
		return;

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		bTutorialAtivado = false;
		SaveInst->bNovoJogo = false;
		bNovoJogo = SaveInst->bNovoJogo;

		NumJogos = SaveInst->NumJogos;
		LevelAtual = SaveInst->LevelAtual;

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXGameMode::LoadProximaFase()
{
	if (bNaoSalvar)
		return;

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		bTutorialAtivado = false;

		SaveInst->bNovoJogo = false;
		bNovoJogo = SaveInst->bNovoJogo;

		SaveInst->LevelAtual++;
		LevelAtual = SaveInst->LevelAtual;

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

