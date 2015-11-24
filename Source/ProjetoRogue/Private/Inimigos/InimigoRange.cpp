// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "InimigoRange.h"
#include "Projectil.h"

AInimigoRange::AInimigoRange(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	Stats.TipoAtaque = ETipoAtaque::RANGE;
	TipoInimigo = ETipoInimigo::TORRE;
	NumProjeteis = 10;
}

void AInimigoRange::BeginPlay()
{
	Super::BeginPlay();

	GerarProjetilPool(); //gerar o pool de projeteis
}

void AInimigoRange::Destroyed()
{
	ProjetilPool.Empty(); //esvaziar o pool de projeteis

	Super::Destroyed();
}

void AInimigoRange::CalcularStats(int32 levelAtual)
{
	Super::CalcularStats(levelAtual);

	Stats.FireRate += (levelAtual - 1)* 1.0f;
	Stats.Precisao += (levelAtual - 1) * 0.5f;
	Stats.VelProjetil += (levelAtual - 1) * 400.0f;
}

void AInimigoRange::GerarProjetilPool()
{
	if (ProjetilPool.Num() > 0) //se o pool já possui projéteis, esvaziar o pool
	{
		ProjetilPool.Empty();
	}

	for (int32 index = 0; index < NumProjeteis; index++) //criar um novo pool de projéteis
	{
		FVector tiroPos = FVector(GetActorLocation().X, GetActorLocation().Y, 1000);

		AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(Projetil, tiroPos, GetControlRotation());

		if (Tiro->IsValidLowLevelFast())
		{
			Tiro->Instigator = this; //setar esse inimigo como o responsável pelo dano causado pelo projetil.
			Tiro->SetActorHiddenInGame(true); //esconder o projétil
			Tiro->Instigator = this;
			ProjetilPool.Add(Tiro);
		}
	}
}

void AInimigoRange::Atirar_Implementation()
{
	for (auto const& proj : ProjetilPool) //checar o primeiro projétil nao ativo dentro do pool de projéteis
	{
		if (!proj->bAtivo)
		{
			//Determinar a posicao da onde o tiro sai, com a rotação apontada para o jogador com um desvio randômico.
			FVector PosTiro = GetPosicaoTiro();
			FRotator tiroDirecao = GetDirecaoTiro();
			FVector direcao = FMath::VRandCone(tiroDirecao.Vector(), FMath::DegreesToRadians(Stats.Precisao / 2.0f));

			//Ativar o projétil atirado e gerar os efeitos de tiro.
			proj->AtivarProjetil(PosTiro, direcao.Rotation(), this);
			proj->GerarEfeitosTiro(PosTiro, tiroDirecao, GetMesh(), TEXT("Tiro_Bocal"));
			break;
		}
	}

}

