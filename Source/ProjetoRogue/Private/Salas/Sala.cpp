// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Sala.h"
#include "Public/Inimigos/Inimigo.h"


// Sets default values
ASala::ASala()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanBeDamaged = false;
	NumeroPortas = ENumeroPortas::UMA;
	DirecaoSala = EFormatoSala::PADRAO;
	TipoSala = ETipoSala::NORMAL;
	Dificuldade = EDificuldadeSala::FACIL;
	SalasConectadas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	bVisitada = false;
	bSalaTemInimigos = false;
	OffsetSala = 4640.0f;
	EscalaPadrao = FVector(5.0f, 5.0f, 5.0f);


}

FVector ASala::GetEscala()
{
	return EscalaPadrao;
}

int32 ASala::GetOffset()
{
	return OffsetSala;
}

ENumeroPortas ASala::GetNumPortas()
{
	return NumeroPortas;
}

EFormatoSala ASala::GetDirecao()
{
	return DirecaoSala;
}

ETipoSala ASala::GetTipo()
{
	return TipoSala;
}

TArray<TEnumAsByte<EDirecaoPorta>> ASala::GetArrayPortas()
{
	return DirecaoPortas;
}

void ASala::SpawnInimigos(int32 Seed)
{
	if (!bSalaTemInimigos || TipoSala == ETipoSala::BOSS)
		return;

	TInlineComponentArray<UBillboardComponent*> Componentes;
	this->GetComponents(Componentes);

	switch (Dificuldade)
	{
	case EDificuldadeSala::FACIL:

		for (const auto& Spawner : Componentes)
		{
			FTransform SpawnTrans = FTransform(FRotator::ZeroRotator, Spawner->GetComponentLocation());

			AInimigo* NovoInimigo = GetWorld()->SpawnActor<AInimigo>(GetTipoInimigo(InimigosFacil, Seed), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			if (NovoInimigo->IsValidLowLevelFast())
			{
				NovoInimigo->SpawnDefaultController();
			}
		}	

		break;
	case EDificuldadeSala::NORMAL:

		for (const auto& Spawner : Componentes)
		{
			FTransform SpawnTrans = FTransform(FRotator::ZeroRotator, Spawner->GetComponentLocation());

			AInimigo* NovoInimigo = GetWorld()->SpawnActor<AInimigo>(GetTipoInimigo(InimigosNormal, Seed), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			if (NovoInimigo->IsValidLowLevelFast())
			{
				NovoInimigo->SpawnDefaultController();
			}
		}

		break;
	case EDificuldadeSala::DIFICIL:

		for (const auto& Spawner : Componentes)
		{
			FTransform SpawnTrans = FTransform(FRotator::ZeroRotator, Spawner->GetComponentLocation());

			AInimigo* NovoInimigo = GetWorld()->SpawnActor<AInimigo>(GetTipoInimigo(InimigosDificil, Seed), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			if (NovoInimigo->IsValidLowLevelFast())
			{
				NovoInimigo->SpawnDefaultController();
			}
		}

		break;
	default:
		break;
	}
}

TSubclassOf<AInimigo> ASala::GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade, int32 Seed)
{
	FRandomStream Stream = FRandomStream(Seed);

	TSubclassOf<AInimigo> tipoInimigo = InimigoDificuldade[Stream.FRandRange(0, InimigoDificuldade.Num() - 1)];

	return tipoInimigo;
	
}

