// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Inimigos/Inimigo.h"
#include "Public/Salas/Sala.h"
#include "Public/Projeteis/Projectil.h"
#include "Public/Itens/PickUpEnergia.h"
#include "Public/Itens/PickUpMoeda.h"
#include "Public/Itens/PickUpVida.h"


// Sets default values
AInimigo::AInimigo()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = FInimigoStats();
	NumPickUps = 1;
	ChanceSpawnVida = 10;
	ChanceSpawnEnergia = 5;
	ChanceSpawnMoeda = 3;

}

// Called when the game starts or when spawned
void AInimigo::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInimigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!EstaVivo())
	{
		SpawnPickUp();
		SalaPai->RemoverInimigo(this);
		Destroy();
	}

}

void AInimigo::ReceberDano(const float& dano)
{
	Stats.Vida -= dano;
}

void AInimigo::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil->IsValidLowLevelFast())
	{
		projetil->Stats = this->Stats;
	}
}

bool AInimigo::EstaVivo()
{
	if (Stats.Vida > 0)
	{
		return true;
	}

	return false;
}

void AInimigo::SpawnPickUp()
{
	const float EXPLOSAO_DELTA = 15.0f;

	FRandomStream stream = FRandomStream();

	for (int32 index = 0; index < NumPickUps; index++)
	{
		stream.GenerateNewSeed();

		if (stream.FRandRange(0, ChanceSpawnVida) == 0)
		{
			APickUpVida* pickSpawn = GetWorld()->SpawnActor<APickUpVida>(PickUpVidaClass, GetActorLocation(), GetActorRotation());

			if (pickSpawn)
			{
				FVector origem = FVector(stream.FRandRange(pickSpawn->GetActorLocation().X - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().X + EXPLOSAO_DELTA),
					stream.FRandRange(pickSpawn->GetActorLocation().Y - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().Y + EXPLOSAO_DELTA),
					pickSpawn->GetActorLocation().Z - EXPLOSAO_DELTA * 10.0f);

				pickSpawn->GetColisor()->AddRadialImpulse(origem, 50.0f, stream.FRandRange(25, 50.0f), ERadialImpulseFalloff::RIF_Constant);
			}

			continue;
		}

		if (stream.FRandRange(0, ChanceSpawnEnergia) == 0)
		{
			APickUpEnergia* pickSpawn = GetWorld()->SpawnActor<APickUpEnergia>(PickUpEnergiaClass, GetActorLocation(), GetActorRotation());

			if (pickSpawn)
			{

				FVector origem = FVector(stream.FRandRange(pickSpawn->GetActorLocation().X - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().X + EXPLOSAO_DELTA),
					stream.FRandRange(pickSpawn->GetActorLocation().Y - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().Y + EXPLOSAO_DELTA),
					pickSpawn->GetActorLocation().Z - EXPLOSAO_DELTA * 10.0f);

				pickSpawn->GetColisor()->AddRadialImpulse(origem, 50.0f, stream.FRandRange(25, 50.0f), ERadialImpulseFalloff::RIF_Constant);
			}

			continue;
		}

		if (stream.FRandRange(0, ChanceSpawnMoeda) == 0)
		{
			APickUpMoeda* pickSpawn = GetWorld()->SpawnActor<APickUpMoeda>(PickUpMoedaClass, GetActorLocation(), GetActorRotation());

			if (pickSpawn)
			{
				FVector origem = FVector(stream.FRandRange(pickSpawn->GetActorLocation().X - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().X + EXPLOSAO_DELTA),
					stream.FRandRange(pickSpawn->GetActorLocation().Y - EXPLOSAO_DELTA, pickSpawn->GetActorLocation().Y + EXPLOSAO_DELTA),
					pickSpawn->GetActorLocation().Z - EXPLOSAO_DELTA * 10.0f);

				pickSpawn->GetColisor()->AddRadialImpulse(origem, 50.0f, stream.FRandRange(25, 50.0f), ERadialImpulseFalloff::RIF_Constant);
			}

			continue;
		}




	}

}
