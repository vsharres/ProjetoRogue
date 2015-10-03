// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "ItemPassivo.generated.h"

/*
* Classe derivada da classe UItem
* Classe que representa um item passivo, onde os stats do item são automaticamente aplicados ao jogador, e o jogador pode ter mais de um item passivo.
*/
UCLASS()
class PROJETOROGUE_API UItemPassivo : public UItem
{
	GENERATED_BODY()

public:
#pragma region Construtor

	/* Construtor Padrão */
	UItemPassivo();

#pragma endregion Construtor

#pragma region FUNÇÕES

	/*
	* Override da função para aplicar os stats do item passivo ao jogador.
	*/
	virtual void AplicarItem_Implementation() override;

	/*
	* Override da função para remover os stats do item passivo ao jogador.
	*/
	virtual void RemoverItem_Implementation() override;


#pragma endregion FUNÇÕES

};
