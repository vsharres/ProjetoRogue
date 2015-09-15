// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Item.h"
#include "Jogador.h"

UItem::UItem()
{
	Stats = FItemStats();
}

TArray<FString> UItem::GetNomeEfeitos()
{
	TArray<FString> ARetornar;

	if (Stats.IncrementaDano != 0.0f)
	{
		ARetornar.Add("Dano");
	}

	if (Stats.IncrementaEnergia != 0)
	{
		ARetornar.Add("Energia");
	}

	if (Stats.IncrementaEnergiaMax != 0)
	{
		ARetornar.Add("Energia Máxima");
	}

	if (Stats.IncrementaFireRate != 0.0f)
	{
		ARetornar.Add("Frequência de Tiro");
	}

	if (Stats.IncrementaPrecisao != 0.0f)
	{
		ARetornar.Add("Tamanho do projétil");
	}

	if (Stats.IncrementaVel != 0.0f)
	{
		ARetornar.Add("Velocidade");
	}

	if (Stats.IncrementaVelProjetil != 0.0f)
	{
		ARetornar.Add("Velocidade do Projétil");
	}

	if (Stats.IncrementaVida != 0.0f)
	{
		ARetornar.Add("Vida");
	}

	if (Stats.IncrementaVidaMax != 0.0f)
	{
		ARetornar.Add("Vida Máxima");
	}

	return ARetornar;

}

TArray<float> UItem::GetEfeitos()
{
	TArray<float> ARetornar;

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
	if (inicializador)
	{
		this->Jogador = inicializador;
		AplicarItem();
	}
}

void UItem::AplicarStats()
{
	Jogador->Stats += Stats;
	Jogador->AtualizarPropriedadesComStats();
}

void UItem::RemoverStats()
{
	Jogador->Stats -= Stats;
	Jogador->AtualizarPropriedadesComStats();
}

void UItem::AplicarItem_Implementation()
{
	AplicarStats();
}

void UItem::RemoverItem_Implementation()
{
	RemoverStats();

	this->BeginDestroy();
}

UObject* UItem::InstanciarItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UItem> Classe)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		UObject* temp = NewObject<UObject>(World,Classe);

		return temp;
	}

	return NULL;

}


