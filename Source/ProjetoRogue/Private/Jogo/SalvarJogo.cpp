// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Public/Jogo/SalvarJogo.h"


USalvarJogo::USalvarJogo(const FObjectInitializer& ObjectInitializer)
{
	//Inicializando as propriedades de um save game.
	SaveSlot = "ProtuX_Save";
	Userindex = 0;

	NumJogos = 0;
	LevelAtual = 0;
	bNovoJogo = true;

	MaxNumSalas = 5;
	MinNumSalas = 5;

	ItensComprados.AddDefaulted(3);

	bMute = false;
	MasterVol = 1.0f;
	MusicVol = 1.0f;
	EffectsVol = 1.0f;
}
