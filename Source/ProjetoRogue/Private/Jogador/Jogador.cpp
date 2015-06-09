// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Projeteis/Projectil.h"
#include "Public/Itens/ItemAtivo.h"

// Sets default values
AJogador::AJogador()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Stats = FJogadorStats();
	bPossuiChave = false;
	ItemAtivoAtual = NULL;
	ItensPassivos.Empty();
	CooldDownRate = 1.0f;
	TempoCooldown = 2.0f;
	CooldownAtual = TempoCooldown;

	NumProjeteis = 10;
	ProjetilAtual = AProjectil::StaticClass();

	

}

void AJogador::AtualizarStats()
{
	GetCharacterMovement()->MaxWalkSpeed = Stats.VelocidadeMov;
}

//TODO
// Called when the game starts or when spawned
void AJogador::BeginPlay()
{
	Super::BeginPlay();

	if (ProjetilAtual->IsValidLowLevel())
	{
		for (int32 i = 0; i < NumProjeteis; i++)
		{
			AProjectil* projeTemp = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual, FVector::ZeroVector, FRotator::ZeroRotator);

			if (projeTemp->IsValidLowLevelFast())
			{
				projeTemp->SetActorHiddenInGame(true);
				PoolProjeteis.Add(projeTemp);
			}
		}
	}
	
}

// Called every frame
void AJogador::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (CooldownAtual < TempoCooldown)
	{
		CooldownAtual += CooldDownRate * DeltaTime;
	}
	else
	{
		CooldownAtual = TempoCooldown;
		if (ItemAtivoAtual->IsValidLowLevelFast() && ItemAtivoAtual->bAtivo)
		{
			ItemAtivoAtual->DesativarItem();
		}
	}

}

// Called to bind functionality to input
void AJogador::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

