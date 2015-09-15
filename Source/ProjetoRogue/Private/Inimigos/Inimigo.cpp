// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Inimigos/Inimigo.h"
#include "Sala.h"
#include "Projectil.h"
#include "PickUpEnergia.h"
#include "PickUpMoeda.h"
#include "PickUpVida.h"

// Sets default values
AInimigo::AInimigo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = FInimigoStats();
	NumPickUps = 1;
	ChanceSpawnVida = 90.0f;
	ChanceSpawnEnergia = 60.0f;
	ChanceSpawnMoeda = 30.0f;

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

void AInimigo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	

	Super::EndPlay(EndPlayReason);
}

void AInimigo::ReceberDano(const float& dano)
{
	Stats.Vida -= dano;

	AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (jogador)
	{
		jogador->GerarDanoPopUp(dano, this);
	}
}

void AInimigo::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil)
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
	const float EXPLOSAO_DELTA = 50.0f;

	FRandomStream stream = FRandomStream();

	for (int32 index = 0; index < NumPickUps; index++)
	{
		if (stream.FRandRange(0, 100) >= ChanceSpawnVida)
		{
			APickUpVida* pickSpawn = GetWorld()->SpawnActor<APickUpVida>(PickUpVidaClass, GetActorLocation(), GetActorRotation());

			if (pickSpawn)
			{
				FVector origem = FVector(stream.FRandRange(GetActorLocation().X - EXPLOSAO_DELTA, GetActorLocation().X + EXPLOSAO_DELTA),
					stream.FRandRange(GetActorLocation().Y - EXPLOSAO_DELTA, GetActorLocation().Y + EXPLOSAO_DELTA),
					GetActorLocation().Z - EXPLOSAO_DELTA * 10.0f);

				pickSpawn->GetColisor()->AddRadialImpulse(origem, 500.0f, stream.FRandRange(25, 50.0f), ERadialImpulseFalloff::RIF_Constant);
			}

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnEnergia)
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

		if (stream.FRandRange(0, 100) >= ChanceSpawnMoeda)
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


