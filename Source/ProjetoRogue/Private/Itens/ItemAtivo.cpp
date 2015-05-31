// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemAtivo.h"

AItemAtivo::AItemAtivo()
{
	Tipo = ETipoItem::ATIVO;
	Stats = FItemStats();
	bAtivo = false;
	Cooldown = 10.0f;
}


