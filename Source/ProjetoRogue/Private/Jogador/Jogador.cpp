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
	bVivo = true;
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

bool AJogador::EstaVivo()
{
	if (Stats.Vida > 0)
	{
		return true;
	}

	return false;
}

//TODO
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
		if (ItemAtivoAtual->IsValidLowLevelFast() && ItemAtivoAtual->bAtivo)
		{
			ItemAtivoAtual->DesativarItem();
		}
	}

	bVivo = EstaVivo();

}

// Called to bind functionality to input
void AJogador::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AJogador::ReceberDano(const float& dano)
{
	this->Stats.Vida -= dano;
}

void AJogador::Atirar()
{

}

