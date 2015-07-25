// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Inimigos/InimigoRange.h"

AInimigoRange::AInimigoRange()
{
	Stats.Tipo = ETipoInimigo::TORRE;
	Stats.TipoAtaque = ETipoAtaque::RANGE;
}

void AInimigoRange::Atirar_Implementation()
{

}

