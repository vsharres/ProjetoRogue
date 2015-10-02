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
		if (SalaPai->IsValidLowLevelFast())
		{
			SalaPai->RemoverInimigo(this);
		}
		Destroy();
	}


}

void AInimigo::ReceberDano(const float& dano, AProjectil* projetil)
{
	Stats.Vida -= dano;
	this->FlashDano();
	AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (jogador->IsValidLowLevelFast())
	{
		jogador->GerarDanoPopUp(dano, this, projetil);
	}
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
	FRandomStream stream = FRandomStream();
	stream.GenerateNewSeed();

	for (int32 index = 0; index < NumPickUps; index++)
	{
		if (stream.FRandRange(0, 100) >= ChanceSpawnVida)
		{

			APickUpVida* pickSpawn = GetWorld()->SpawnActor<APickUpVida>(PickUpVidaClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnEnergia)
		{

			APickUpEnergia* pickSpawn = GetWorld()->SpawnActor<APickUpEnergia>(PickUpEnergiaClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnMoeda)
		{
			APickUpMoeda* pickSpawn = GetWorld()->SpawnActor<APickUpMoeda>(PickUpMoedaClass, GetActorLocation(), GetActorRotation());

			continue;
		}

	}

}


