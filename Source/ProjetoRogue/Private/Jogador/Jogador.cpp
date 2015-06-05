// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Itens/ItemAtivo.h"


// Sets default values
AJogador::AJogador()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Stats = FJogadorStats();
	bPossuiChave = false;
	AtivoAtual = NULL;
	ItensPassivos.Empty();
	CooldDownRate = 1.0f;
	TempoCooldown = 10.0f;
	CooldownAtual = TempoCooldown;

}

// Called when the game starts or when spawned
void AJogador::BeginPlay()
{
	Super::BeginPlay();
	
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
		if (AtivoAtual->IsValidLowLevelFast() && AtivoAtual->bAtivo)
		{
			AtivoAtual->DesativarItem();
		}
	}

}

// Called to bind functionality to input
void AJogador::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

