// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "SalvarJogo.h"


USalvarJogo::USalvarJogo(const FObjectInitializer& ObjectInitializer)
{
	SaveSlot = "ProtuX_Save";
	Userindex = 0;

	NumJogos = 0;
	bNovoJogo = true;
}
