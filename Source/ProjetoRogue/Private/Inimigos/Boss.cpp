// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Boss.h"


ABoss::ABoss(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	TipoInimigo = ETipoInimigo::BOSS;
	Armadura = 0.5f;

	PontoFraco = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("PontoFraco"));
	PontoFraco->AttachTo(GetMesh());

}

void ABoss::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	this->FlashDano(); //fazer o flash do mesh do boss
	AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Hit.GetComponent() == PontoFraco) //se o ponto fraco do boss foi atingido, causar o dano normal, se não causar um dano reduzido
	{
		Stats.Vida -= dano;
		if (jogador->IsValidLowLevelFast())
		{
			jogador->GerarDanoPopUp(dano, this, projetil); //gerar o popup com o dano causado
		}
	}
	else
	{
		Stats.Vida -= dano * Armadura;
		if (jogador->IsValidLowLevelFast())
		{
			jogador->GerarDanoPopUp(dano* Armadura, this, projetil); //gerar o popup com o dano causado
		}
	}
	
}
