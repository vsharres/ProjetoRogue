// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "InimigoRange.h"
#include "Projectil.h"

AInimigoRange::AInimigoRange()
{
	Stats.Tipo = ETipoInimigo::TORRE;
	Stats.TipoAtaque = ETipoAtaque::RANGE;
	NumProjeteis = 10;
}

void AInimigoRange::BeginPlay()
{
	Super::BeginPlay();

	GerarProjetilPool();
}

void AInimigoRange::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	ProjetilPool.Empty();

	Super::EndPlay(EndPlayReason);
}

void AInimigoRange::GerarProjetilPool()
{
	if (ProjetilPool.Num() > 0)
	{
		ProjetilPool.Empty();
	}

	for (int32 index = 0; index < NumProjeteis; index++)
	{
		FVector tiroPos = FVector(GetActorLocation().X, GetActorLocation().Y, -1000);
		FActorSpawnParameters params;
		params.bNoCollisionFail = true;

		AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(Projetil, tiroPos, GetControlRotation(), params);

		if (Tiro->IsValidLowLevel())
		{
			Tiro->SetActorHiddenInGame(true);
			Tiro->Instigator = this;
			ProjetilPool.Add(Tiro);
		}
	}
}

void AInimigoRange::Atirar_Implementation()
{
	for (auto const& proj : ProjetilPool)
	{
		if (!proj->bAtivo)
		{
			FVector pos = GetActorLocation() + GetActorForwardVector() * 100;
			FRotator rot = GetActorRotation();

			proj->AtivarProjetil(pos, rot, this);
			break;
		}
	}




}

