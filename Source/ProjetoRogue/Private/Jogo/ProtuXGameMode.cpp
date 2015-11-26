// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "InimigosControlador.h"
#include "ProtuXGameMode.h"


AProtuXGameMode::AProtuXGameMode(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades.
	bNovoJogo = true;
	bNaoSalvar = false;
	LevelAtual = 0;

}


EJogoEstado AProtuXGameMode::GetEstadoJogo() const
{
	return Estado;
}

void AProtuXGameMode::SetEstadoJogo(EJogoEstado NovoEstado)
{
	Estado = NovoEstado; //Set novo estado

	AtualizarEstado(NovoEstado); //Atualizar state machine
}

void AProtuXGameMode::AtualizarEstado(EJogoEstado NovoEstado)
{
	APlayerController* controlador; //Controlador do jogador
	TArray<AActor*> InimigosControladores; //Controladores dos inimigos

	switch (NovoEstado)
	{

	case EJogoEstado::MENUPRINCIPAL: //Abrir o menu principal
		UGameplayStatics::OpenLevel(this, TEXT("MenuPrincipal"), true);
		break;
	case EJogoEstado::NOVOJOGO: //Fazer o load do profile de novo jogo e abrir o level inicial
		LoadNovoJogo();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		break;
	case EJogoEstado::PROXIMAFASE: //Fazer o load do profile de nova fase e abrir o level.
		LoadProximaFase();
		UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		break;
	case EJogoEstado::CONTINUARJOGO:
		LoadContinuarJogo();
		if (LevelAtual > 1)
		{
			UGameplayStatics::OpenLevel(this, TEXT("ProximoLevel"), false);
		}
		else
		{
			UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), false);
		}
		break;
	case EJogoEstado::GAMEOVER: 

		UGameplayStatics::GetAllActorsOfClass(this, AAIController::StaticClass(), InimigosControladores);

		for (auto Actor : InimigosControladores) //Desativar todos os inimigos
		{
			AInimigosControlador* inimgControlador = Cast<AInimigosControlador>(Actor);

			if (inimgControlador->IsValidLowLevelFast())
			{
				inimgControlador->DesativarInimigo();
			}
		}

		controlador = UGameplayStatics::GetPlayerController(this, 0); //Desativar o controle do jogador.

		if (controlador->IsValidLowLevelFast())
		{
			controlador->SetCinematicMode(true, true, true);
			controlador->bShowMouseCursor = true;
		}
		break;
	case  EJogoEstado::REINICIAR: //Fazer o load do profile de novo jogo e o level inicial.
		LoadNovoJogo();
		UGameplayStatics::OpenLevel(this, TEXT("LevelInicial"), true);
		break;
	default:
		break;
	}
}

void AProtuXGameMode::LoadNovoJogo()
{
	if (bNaoSalvar)
		return;

	//Criando o objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //Case o save não exista, criar um novo.
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast()) 
	{
		SaveInst->bNovoJogo = true; //Por ser um novo jogo, o save game está como jogo novo.
		SaveInst->bContinuarJogo = false;
		SaveInst->bPossuiChave = false;
		SaveInst->bBossDerrotado = false;
		SaveInst->bItemEncontrado = false;
		SaveInst->ItensComprados.Empty();
		SaveInst->Scrap = 0;
		SaveInst->NumJogos += 1;	
		SaveInst->LevelAtual = 1; //Level atual
		
		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);

	}
}

void AProtuXGameMode::LoadContinuarJogo()
{
	if (bNaoSalvar)
		return;

	//Criando o objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bNovoJogo = false;
		SaveInst->bContinuarJogo = true;
		NumJogos = SaveInst->NumJogos; //Nao incrementar o número de jogos.
		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AProtuXGameMode::LoadProximaFase()
{
	if (bNaoSalvar)
		return;
	
	//Criando o objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bNovoJogo = false; //por ser uma transição para a proxima fase, não incrementar o número de jogos.
		SaveInst->bContinuarJogo = false;
		SaveInst->LevelAtual++; //Incrementar o level atual.
		SaveInst->bItemEncontrado = false;
		SaveInst->bPossuiChave = false;
		SaveInst->ItensComprados.Empty();
		SaveInst->bBossDerrotado = false;

		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

