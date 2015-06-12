// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Inimigos/Inimigo.h"


// Sets default values
AInimigo::AInimigo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = FInimigoStats();
	bVivo = true;

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

	bVivo = EstaVivo();

	if (!bVivo)
	{
		Destroy();
	}

}

void AInimigo::ReceberDano(const float& dano)
{
	Stats.Vida -= dano;
}

bool AInimigo::EstaVivo()
{
	if (Stats.Vida > 0)
	{
		return true;
	}

	return false;
}
