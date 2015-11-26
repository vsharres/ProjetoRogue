// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "InimigoSpawnerComponent.h"
#include "Inimigo.h"

UInimigoSpawnerComponent::UInimigoSpawnerComponent()
{
	//Inicializando propriedades
	bGerarRandomicamente = false;
}

int32 UInimigoSpawnerComponent::GetNumInimigos(EDificuldadeSala Dificuldade)
{
	int32 num;

	switch (Dificuldade) //retornar o número de inimigos de acordo com a dificuldade
	{
	case EDificuldadeSala::NORMAL:
		num = InimigosRandomicosNormal.Num();
		break;
	case EDificuldadeSala::DIFICIL:
		num = InimigosRandomicosDificil.Num();
		break;
	default:
		num = 0;
		break;
	}

	return num;
}

TSubclassOf<AInimigo> UInimigoSpawnerComponent::SelecionarInimigoRandomicamente(FRandomStream& Stream, EDificuldadeSala Dificuldade)
{
	TSubclassOf<AInimigo> classe;

	//selecionar randomicamente um inimigo de acordo com a dificuldade
	switch (Dificuldade)
	{
	case EDificuldadeSala::NORMAL:
		classe = InimigosRandomicosNormal[Stream.FRandRange(0, InimigosRandomicosNormal.Num() - 1)]; 
		break;
	case EDificuldadeSala::DIFICIL:
		classe = InimigosRandomicosDificil[Stream.FRandRange(0, InimigosRandomicosDificil.Num() - 1)];
		break;
	}

	return classe;
}
