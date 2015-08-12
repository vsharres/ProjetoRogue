// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Projeteis/Projectil.h"
#include "Public/Itens/ItemAtivo.h"
#include "Public/Itens/ItemProjetil.h"

// Sets default values
AJogador::AJogador(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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
	Moedas = 0;
	CooldownAtual = TempoCooldown;
	bItemEncontrado = false;

	NumProjeteis = 10;

	Nome = "Mark I";

}

void AJogador::InicializarJogador()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	if (gameMode->bNovoJogo)
	{
		NovoJogador();
	}
	else
	{
		CarregarJogador();
	}
}

void AJogador::GerarNome(int32 index)
{
	FString num;

	int32 temp = index;

	while (temp != 0 && temp <= 999)
	{
		if (temp >= 100)
		{
			switch (temp / 100)
			{
			case 1:
				num += "C";
				break;
			case 2:
				num += "CC";
				break;
			case 3:
				num += "CCC";
				break;
			case 4:
				num += "CD";
				break;
			case 5:
				num += "D";
				break;
			case 6:
				num += "DC";
				break;
			case 7:
				num += "DCC";
				break;
			case 8:
				num += "DCCC";
				break;
			case 9:
				num += "MC";
				break;
			default:
				break;
			}

			temp = temp - (temp / 100 * 100);
		}
		else if (temp >= 10)
		{

			switch (temp / 10)
			{
			case 1:
				num += "X";
				break;
			case 2:
				num += "XX";
				break;
			case 3:
				num += "XXX";
				break;
			case 4:
				num += "XL";
				break;
			case 5:
				num += "L";
				break;
			case 6:
				num += "LX";
				break;
			case 7:
				num += "LXX";
				break;
			case 8:
				num += "LXXX";
				break;
			case 9:
				num += "XC";
				break;
			default:
				break;
			}

			temp = temp - (temp / 10 * 10);
		}
		else if (temp < 10)
		{
			switch (temp)
			{
			case 1:
				num += "I";
				break;
			case 2:
				num += "II";
				break;
			case 3:
				num += "III";
				break;
			case 4:
				num += "IV";
				break;
			case 5:
				num += "V";
				break;
			case 6:
				num += "VI";
				break;
			case 7:
				num += "VII";
				break;
			case 8:
				num += "VIII";
				break;
			case 9:
				num += "IX";
				break;
			default:
				break;
			}

			temp = 0;

		}

	}

	Nome = "Mark " + num;

}

void AJogador::AtualizarPropriedadesComStats()
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

void AJogador::AdicionarVida(float vida)
{
	this->Stats.Vida += vida;

	if (Stats.Vida > Stats.VidaMaxima)
	{
		Stats.Vida = VIDAMAX_MAX;
	}
}

void AJogador::AdicionarEnerngia(int32 energia)
{
	Stats.Energia += energia;

	if (Stats.Energia > Stats.EnergiaMax)
	{
		Stats.Energia = Stats.EnergiaMax;
	}
}

void AJogador::AdicionarMoedas(int32 valor)
{
	Moedas += valor;

	if (Moedas < 0)
	{
		Moedas = 0;
	}
}


void AJogador::CarregarJogador()
{
	//TODO
}

void AJogador::NovoJogador()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		GerarNome(SaveInst->NumJogos);
	}

}

// Called when the game starts or when spawned
void AJogador::BeginPlay()
{
	Super::BeginPlay();

	InicializarProjetil();


}

void AJogador::InicializarProjetil()
{
	UObject* temp = NewObject<UObject>(this, ProjetilInicial);
	ProjetilAtual = Cast<UItemProjetil>(temp);

	if (ProjetilAtual)
	{
		ProjetilAtual->Jogador = this;
		ProjetilAtual->AplicarItem();
	}

	AtualizarProjetilPool();
}

void AJogador::AtualizarProjetilPool()
{
	if (ProjetilPool.Num() > 0)
	{
		ProjetilPool.Empty();
	}

	for (int32 index = 0; index < NumProjeteis; index++)
	{
		FVector tiroPos = FVector(0, 0, -1000);
		FActorSpawnParameters params;
		params.bNoCollisionFail = true;

		AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual->Projetil, tiroPos, GetControlRotation(), params);

		if (Tiro->IsValidLowLevel())
		{
			Tiro->SetActorHiddenInGame(true);
			Tiro->Instigator = this;
			ProjetilPool.Add(Tiro);
		}
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

//void AJogador::Atirar()
//{
//	FVector tiroPos = GetActorLocation() + (GetActorForwardVector() * 100);
//
//	AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual->Projetil, tiroPos, GetControlRotation());
//
//	if (Tiro)
//	{
//		Tiro->SetActorScale3D(Tiro->GetActorScale3D()*Tiro->Stats.Tamanho);
//		Tiro->InicializarProjetil();
//	}
//
//}

