// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Jogador.h"
#include "Projectil.h"
#include "ItemAtivo.h"
#include "ItemPassivo.h"
#include "ItemProjetil.h"

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
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (gameMode->bNovoJogo)
	{
		NovoJogador();
	}
	else
	{
		CarregarJogador();
	}

	InicializarProjetil();
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
		Stats.Vida = Stats.VidaMaxima;
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


void AJogador::SalvarJogador()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		SaveInst->bNovoJogo = false;
		SaveInst->Stats.SetStats(this->Stats);
		SaveInst->Moedas = this->Moedas;
		SaveInst->bPossuiChave = this->bPossuiChave;

		SaveInst->JogadorLocation = this->GetActorLocation();
		SaveInst->JogadorRotation = this->GetActorRotation();

		if (ProjetilAtual->IsValidLowLevelFast())
		{
			SaveInst->ProjetilInicial_Referencia = FStringAssetReference(this->ProjetilAtual->GetClass()).ToString();
		}

		SaveInst->bItemEncontrado = this->bItemEncontrado;

		if (ItemAtivoAtual->IsValidLowLevelFast())
		{

			SaveInst->ItemAtivo_Referencia = FStringAssetReference(this->ItemAtivoAtual->GetClass()).ToString();
		}

		SaveInst->ItensPassivos_Referencias.Empty();
		for (const auto& item : ItensPassivos)
		{

			SaveInst->ItensPassivos_Referencias.Add(FStringAssetReference(item->GetClass()).ToString());
		}

		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AJogador::CarregarJogador()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast())
	{
		GerarNome(SaveInst->NumJogos);
		this->Stats.SetStats(SaveInst->Stats);
		this->Moedas = SaveInst->Moedas;
		this->bPossuiChave = SaveInst->bPossuiChave;

		this->SetActorLocation(SaveInst->JogadorLocation);
		this->SetActorRotation(SaveInst->JogadorRotation);

		if (this->GetActorLocation().Z < 100.f)
		{
			this->AddActorLocalOffset(FVector(0, 0, 127.f));
		}

		if (!SaveInst->ProjetilInicial_Referencia.IsEmpty())
		{
			UItemProjetil* itemProjetil = NewObject<UItemProjetil>(this, StaticLoadClass(UItemProjetil::StaticClass(), NULL, *SaveInst->ProjetilInicial_Referencia));

			if (itemProjetil->IsValidLowLevelFast())
			{
				this->ProjetilInicial = itemProjetil->GetClass();
			}
		}

		if (!SaveInst->ItemAtivo_Referencia.IsEmpty())
		{
			UItemAtivo* itemAtivo = NewObject<UItemAtivo>(this, StaticLoadClass(UItemAtivo::StaticClass(), NULL, *SaveInst->ItemAtivo_Referencia));

			if (itemAtivo->IsValidLowLevelFast())
			{
				itemAtivo->InicializarItem(this);
			}
		}


		if (SaveInst->ItensPassivos_Referencias.Num() > 0)
		{
			this->ItensPassivos.Empty();
			for (const auto& passivo : SaveInst->ItensPassivos_Referencias)
			{
				UItemPassivo* itemPassivo = NewObject<UItemPassivo>(this, StaticLoadClass(UItemPassivo::StaticClass(), NULL, *passivo));

				if (itemPassivo->IsValidLowLevelFast())
				{
					itemPassivo->InicializarItem(this);
				}
			}
		}

	}

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


void AJogador::InicializarProjetil()
{
	UObject* temp = NewObject<UObject>(this, ProjetilInicial);
	ProjetilAtual = Cast<UItemProjetil>(temp);

	if (ProjetilAtual)
	{
		ProjetilAtual->Jogador = this;
		ProjetilAtual->AplicarItem();
	}

	GerarProjetilPool();
}

void AJogador::GerarProjetilPool()
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


	ItemCooldown(DeltaTime);

}

void AJogador::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ProjetilPool.Empty();
	ItensPassivos.Empty();

	Super::EndPlay(EndPlayReason);
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

	if (Stats.Vida <= 0)
	{
		JogadorMorreu();
	}
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


