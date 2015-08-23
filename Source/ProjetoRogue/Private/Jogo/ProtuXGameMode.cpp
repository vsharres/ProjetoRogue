// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Public/Inimigos/InimigosControlador.h"
#include "Public/Jogo/ProtuXGameMode.h"


AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	bNovoJogo = true;
	
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
	case EJogoEstado::JOGO:
		LoadProfile();
		break;
	case EJogoEstado::GAMEOVER:

		UGameplayStatics::GetAllActorsOfClass(this, AInimigosControlador::StaticClass(), InimigosControladores);

		for (auto Actor : InimigosControladores)
		{
			AInimigosControlador* inimgControlador = Cast<AInimigosControlador>(Actor);

			if (inimgControlador)
			{
				inimgControlador->DesativarInimigo();
			}
		}

		controlador = UGameplayStatics::GetPlayerController(this, 0);

		if (controlador)
		{
			controlador->SetCinematicMode(true, true, true);
			controlador->bShowMouseCursor = true;
		}
		break;
	case  EJogoEstado::REINICIAR:
		UGameplayStatics::OpenLevel(this, TEXT("Prototipo") , true);
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

void AProtuXGameMode::Tick(float DeltaSeconds)
{

}

void AProtuXGameMode::LoadProfile()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex))
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		bNovoJogo = SaveInst->bNovoJogo;

		if (bNovoJogo)
		{
			SaveInst->NumJogos += 1;
		}

		NumJogos = SaveInst->NumJogos;

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
		
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

