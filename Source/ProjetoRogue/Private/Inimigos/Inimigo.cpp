// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Inimigos/Inimigo.h"
#include "Sala.h"
#include "Projectil.h"
#include "PickUpEnergia.h"
#include "PickUpMoeda.h"
#include "PickUpVida.h"
#include "PickUpItem.h"

AInimigo::AInimigo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	PrimaryActorTick.bCanEverTick = true;

	TipoInimigo = ETipoInimigo::DRONE;
	Stats = FInimigoStats();
	NumPickUps = 1;
	ChanceSpawnVida = 90.0f;
	ChanceSpawnEnergia = 75.0f;
	ChanceSpawnScrap = 25.0f;

	bEstaAtacando = false;

}

// Called every frame
void AInimigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!EstaVivo()) //checando se o inimigo está vivo, e se não estiver, remover o inimigo do array de inimigos da salapai
	{
		if (SalaPai->IsValidLowLevelFast())
		{
			SalaPai->RemoverInimigo(this);
		}

		InimigoMorreu(); //disparar o evento para destruir o inimigo.
	}

}

void AInimigo::BeginPlay()
{
	Super::BeginPlay();

	//Criar objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	int32 level = 1;

	if (SaveInst)
	{
		level = SaveInst->LevelAtual;
	}

	CalcularStats(level);

}

FVector AInimigo::GetPosicaoTiro()
{
	return GetMesh()->GetSocketLocation("Tiro_Bocal");
}

FRotator AInimigo::GetDirecaoTiro()
{
	return GetMesh()->GetComponentRotation();
}

void AInimigo::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	Stats.Vida -= dano;
	this->FlashDano(); //evento para gerar o efeito de flash do mesh do inimigo
	AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (jogador->IsValidLowLevelFast())
	{
		jogador->GerarDanoPopUp(dano, this, projetil); //gerar o popup de dano para o jogador
	}

}

void AInimigo::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil->IsValidLowLevelFast()) //aplicar os stats do inimigo ao projetil
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

void AInimigo::CalcularStats(int32 levelAtual)
{
	Stats.Dano += (levelAtual - 1) * 2.5f;
	Stats.Vida += (levelAtual - 1) * 15.0f;
	Stats.VidaMax += (levelAtual - 1) * 15.0f;
}

void AInimigo::SpawnPickUp()
{
	FRandomStream stream = FRandomStream();
	stream.GenerateNewSeed(); //criar novo seed de geração do pickup

	for (int32 index = 0; index < NumPickUps; index++)
	{
		if (index == 0 && TipoInimigo == ETipoInimigo::BOSS) //se o inimigo for um boss, o primeiro pickup é sempre um item
		{
			APickUpItem* pickItem = GetWorld()->SpawnActor<APickUpItem>(PickUpItemClass, GetActorLocation(), GetActorRotation());
			pickItem->EscolherItem(stream);

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnVida) //tentar fazer o spawn de um pickup de vida
		{

			APickUpVida* pickSpawn = GetWorld()->SpawnActor<APickUpVida>(PickUpVidaClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnEnergia) //tentar fazer o spawn de um pickup de energia
		{

			APickUpEnergia* pickSpawn = GetWorld()->SpawnActor<APickUpEnergia>(PickUpEnergiaClass, GetActorLocation(), GetActorRotation());

			continue;
		}

		if (stream.FRandRange(0, 100) >= ChanceSpawnScrap) //tentar fazer o spawn de um pickup de scrap
		{
			APickUpMoeda* pickSpawn = GetWorld()->SpawnActor<APickUpMoeda>(PickUpScrapClass, GetActorLocation(), GetActorRotation());

			continue;
		}

	}

}


