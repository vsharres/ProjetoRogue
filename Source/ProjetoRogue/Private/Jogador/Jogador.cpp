// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Projeteis/Projectil.h"
#include "Public/Itens/ItemAtivo.h"
#include "Public/Itens/ItemProjetil.h"

// Sets default values
AJogador::AJogador()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bDebug = false;

	Stats = FJogadorStats();
	bPossuiChave = false;
	ItemAtivoAtual = NULL;
	ItensPassivos.Empty();
	CooldDownRate = 1.0f;
	TempoCooldown = 2.0f;
	CooldownAtual = TempoCooldown;

	NumProjeteis = 10;
	


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

	UObject* temp = NewObject<UObject>(ProjetilInicial);
	ProjetilAtual = Cast<UItemProjetil>(temp);

	if (ProjetilAtual)
	{
		ProjetilAtual->Jogador = this;
		ProjetilAtual->AplicarItem();
	}
	

}

// Called every frame
void AJogador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDebug)
	{
		Debug();
	}

	ItemCooldown(DeltaTime);


}

void AJogador::ItemCooldown(float DeltaTime)
{
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

void AJogador::ReceberDano(const float& dano)
{
	this->Stats.Vida -= dano;
}

void AJogador::Debug()
{
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, FString::SanitizeFloat(GetControlRotation().Yaw));
#endif
}

void AJogador::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil)
	{
		projetil->Stats = this->Stats;
	}
}

void AJogador::Atirar()
{
	FVector tiroPos = GetActorLocation() + (GetActorForwardVector() * 100);

	AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual->Projetil, tiroPos, GetActorRotation());

	if (Tiro)
	{
		Tiro->SetActorScale3D(Tiro->GetActorScale3D()*Tiro->Stats.Tamanho);
		Tiro->InicializarProjetil();
	}

}

