// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Item.h"
#include "Jogador.h"

UItem::UItem()
{
	//Inicializando os stats do item
	Stats = FItemStats();
}

TArray<FString> UItem::GetNomeEfeitos()
{
	TArray<FString> ARetornar;

	//Criar o array com o nome dos stats que são modificados pelo item
	if (Stats.IncrementaDano != 0.0f)
	{
		ARetornar.Add("Damage");
	}

	if (Stats.IncrementaEnergia != 0)
	{
		ARetornar.Add("Energy");
	}

	if (Stats.IncrementaEnergiaMax != 0)
	{
		ARetornar.Add("Max Energy");
	}

	if (Stats.IncrementaFireRate != 0.0f)
	{
		ARetornar.Add("Fire Rate");
	}

	if (Stats.IncrementaPrecisao != 0.0f)
	{
		ARetornar.Add("Accuracy");
	}

	if (Stats.IncrementaVel != 0.0f)
	{
		ARetornar.Add("Speed");
	}

	if (Stats.IncrementaVelProjetil != 0.0f)
	{
		ARetornar.Add("Muzzle Speed");
	}

	if (Stats.IncrementaVida != 0.0f)
	{
		ARetornar.Add("Health");
	}

	if (Stats.IncrementaVidaMax != 0.0f)
	{
		ARetornar.Add("Max Health");
	}

	return ARetornar;

}

TArray<float> UItem::GetEfeitos()
{
	TArray<float> ARetornar;

	//Criar o array com o valor das propriedades que são alteradas pelo item
	if (Stats.IncrementaDano != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaDano);
	}

	if (Stats.IncrementaEnergia != 0)
	{
		ARetornar.Add(Stats.IncrementaEnergia);
	}

	if (Stats.IncrementaEnergiaMax != 0)
	{
		ARetornar.Add(Stats.IncrementaEnergiaMax);
	}

	if (Stats.IncrementaFireRate != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaFireRate);
	}

	if (Stats.IncrementaPrecisao != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaPrecisao);
	}

	if (Stats.IncrementaVel != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaVel);
	}

	if (Stats.IncrementaVelProjetil != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaVelProjetil);
	}

	if (Stats.IncrementaVida != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaVida);
	}

	if (Stats.IncrementaVidaMax != 0.0f)
	{
		ARetornar.Add(Stats.IncrementaVidaMax);
	}

	return ARetornar;
}

void UItem::InicializarItem(AJogador* inicializador)
{
	if (inicializador->IsValidLowLevelFast())
	{
		this->Jogador = inicializador;
		Stats = Jogador->Stats.ClampAdicionarStats(Stats); //aplicar os stats do item ao jogador, levando em consideração os limites dos stats.
		AplicarItem();
	}
}

void UItem::AplicarStats()
{
	Jogador->Stats += Stats; //aplicar os stats
	Jogador->AtualizarPropriedadesComStats(); //checar os limites 
}

void UItem::RemoverStats()
{
	Jogador->Stats -= Stats; //remover os stats
	Jogador->AtualizarPropriedadesComStats(); //checar os limites 
}

void UItem::AplicarItem_Implementation()
{
	AplicarStats();
}

void UItem::RemoverItem_Implementation()
{
	RemoverStats();

	this->ConditionalBeginDestroy(); //destuir o item
}

UObject* UItem::InstanciarItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine) //checar o ponteiro da instancia do jogo
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		//spawn do item
		UObject* temp = NewObject<UObject>(World,Classe);

		return temp;
	}

	return NULL;

}


