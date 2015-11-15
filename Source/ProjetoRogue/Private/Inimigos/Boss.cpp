// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Boss.h"


ABoss::ABoss(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TipoInimigo = ETipoInimigo::BOSS;
	Armadura = 0.5f;

	PontoFraco = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("PontoFraco"));
	PontoFraco->AttachTo(GetMesh());

}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABoss::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	this->FlashDano();
	AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Hit.GetComponent() == PontoFraco)
	{
		Stats.Vida -= dano;
		if (jogador->IsValidLowLevelFast())
		{
			jogador->GerarDanoPopUp(dano, this, projetil);
		}
	}
	else
	{
		Stats.Vida -= dano * Armadura;
		if (jogador->IsValidLowLevelFast())
		{
			jogador->GerarDanoPopUp(dano* Armadura, this, projetil);
		}
	}
	
}
