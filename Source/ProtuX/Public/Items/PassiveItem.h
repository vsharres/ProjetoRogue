// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "PassiveItem.generated.h"

/*
* Classe derivada da classe UItem
* Classe que representa um item passivo, onde os stats do item são automaticamente aplicados ao jogador, e o jogador pode ter mais de um item passivo.
*/
UCLASS()
class PROTUX_API UPassiveItem : public UItem
{
	GENERATED_BODY()

public:
#pragma region Constructor

	/* Constructor Padrão */
	UPassiveItem();

#pragma endregion Constructor

#pragma region Functions

	/*
	* Override da função para aplicar os stats do item passivo ao jogador.
	*/
	virtual void ApplyItem_Implementation() override;

	/*
	* Override da função para remover os stats do item passivo ao jogador.
	*/
	virtual void RemoveItem_Implementation() override;


#pragma endregion Functions

};
