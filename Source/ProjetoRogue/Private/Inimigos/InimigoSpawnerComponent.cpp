// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Inimigo.h"
#include "InimigoSpawnerComponent.h"

UInimigoSpawnerComponent::UInimigoSpawnerComponent()
{
	bGerarRandomicamente = false;
}

TSubclassOf<AInimigo> UInimigoSpawnerComponent::SelecionarInimigoRandomicamente(FRandomStream& Stream)
{
	TSubclassOf<AInimigo> classe = InimigosRandomicos[Stream.FRandRange(0, InimigosRandomicos.Num() - 1)];

	return classe;
}
