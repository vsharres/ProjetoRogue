// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Inimigos/Inimigo.h"
#include "Public/Salas/Sala.h"
#include "Public/Projeteis/Projectil.h"


// Sets default values
AInimigo::AInimigo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = FInimigoStats();

}

// Called when the game starts or when spawned
void AInimigo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInimigo::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!EstaVivo())
	{
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
