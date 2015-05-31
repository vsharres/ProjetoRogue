// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Itens/ItemPassivo.h"

AItemPassivo::AItemPassivo()
{
	Tipo = ETipoItem::PASSIVO;
	Stats = FItemStats();
}


