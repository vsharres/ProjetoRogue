// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Jogador.h"
#include "Projectil.h"
#include "ItemPassivo.h"
#include "ItemProjetil.h"

// Sets default values
AJogador::AJogador(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = FJogadorStats();
	bPossuiChave = false;
	ItensPassivos.Empty();
	CooldDownRate = 1.0f;
	TempoCooldown = 2.0f;
	Moedas = 0;
	CooldownAtual = TempoCooldown;
	bItemEncontrado = false;

	NumProjeteis = 20;

	Nome = "Mark I";

}

void AJogador::InicializarJogador()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (gameMode->bNovoJogo || gameMode->bNaoSalvar)
	{
		NovoJogador();
	}
	else
	{
		CarregarJogador();
	}

	InicializarProjetil(false);
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
	if (Stats.Vida > 0.01)
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

void AJogador::AdicionarEnerngia(float energia)
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
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNaoSalvar)
		return;

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bNovoJogo = false;
		SaveInst->Stats.SetStats(this->Stats);
		SaveInst->Moedas = this->Moedas;
		SaveInst->bPossuiChave = this->bPossuiChave;

		SaveInst->JogadorLocation = this->GetActorLocation();
		SaveInst->JogadorRotation = this->GetActorRotation();

		if (ProjetilEncontrado)
		{
			SaveInst->ProjetilEncontrado_Referencia = FStringAssetReference(this->ProjetilEncontrado).ToString();
		}

		SaveInst->bItemEncontrado = this->bItemEncontrado;

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

	if (SaveInst)
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

		if (!SaveInst->ProjetilEncontrado_Referencia.IsEmpty())
		{
			UItemProjetil* itemProjetil = NewObject<UItemProjetil>(this, StaticLoadClass(UItemProjetil::StaticClass(), NULL, *SaveInst->ProjetilEncontrado_Referencia));

			if (itemProjetil)
			{
				this->ProjetilEncontrado = itemProjetil->GetClass();
			}
		}


		if (SaveInst->ItensPassivos_Referencias.Num() > 0)
		{
			this->ItensPassivos.Empty();
			for (const auto& passivo : SaveInst->ItensPassivos_Referencias)
			{
				UItemPassivo* itemPassivo = NewObject<UItemPassivo>(this, StaticLoadClass(UItemPassivo::StaticClass(), NULL, *passivo));

				if (itemPassivo)
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

	if (SaveInst)
	{
		GerarNome(SaveInst->NumJogos);
	}

}

void AJogador::UsarItem(bool bDesativar)
{
	if (ProjetilEncontrado->IsValidLowLevelFast())
	{
		InicializarProjetil(bDesativar);
		AtualizarMesh();
	}
}

void AJogador::InicializarProjetil(bool bDesativar)
{
	if (ProjetilAtual ==  NULL && !bDesativar)
	{
		ProjetilAtual = NewObject<UItemProjetil>(this, ProjetilInicial);
		ProjetilAtual->InicializarItem(this);
		GerarProjetilPool();

	}
	else if (bDesativar)
	{
		ProjetilAtual->DesativarItem();
		ProjetilAtual->RemoverItem();
		ProjetilAtual = NewObject<UItemProjetil>(this, ProjetilInicial);
		ProjetilAtual->InicializarItem(this);
		GerarProjetilPool();
	}
	else
	{
		ProjetilAtual->DesativarItem();
		ProjetilAtual->RemoverItem();
		ProjetilAtual = NewObject<UItemProjetil>(this, ProjetilEncontrado);
		ProjetilAtual->InicializarItem(this);
		GerarProjetilPool();

		ProjetilAtual->AtivarItem();
	}

}

void AJogador::GerarProjetilPool()
{
	if (ProjetilPool.Num() > 0)
	{
		ProjetilPool.Empty();
	}

	for (int32 index = 0; index < NumProjeteis; index++)
	{
		FVector tiroPos = FVector(0, 0, 1000);

		AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual->Projetil, tiroPos, GetControlRotation());

		if (Tiro->IsValidLowLevelFast())
		{
			Tiro->Instigator = this;
			Tiro->SetActorHiddenInGame(true);
			Tiro->Instigator = this;
			ProjetilPool.Add(Tiro);
		}
	}

	UMaterialInstanceDynamic* MID;
	MID = ProjetilPool[0]->GetProjetilMesh()->CreateDynamicMaterialInstance(0, ProjetilPool[0]->GetProjetilMesh()->GetMaterial(0));

	if (MID)
	{
		MID->GetVectorParameterValue("Base_Cor", ProjetilCor);
	}

}

// Called every frame
void AJogador::Tick(float DeltaTime)
{
	//ItemCooldown(DeltaTime);

	Super::Tick(DeltaTime);
}

void AJogador::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ProjetilPool.Empty();
	ItensPassivos.Empty();

	Super::EndPlay(EndPlayReason);
}

void AJogador::ItemCooldown(float DeltaTime)
{
	if (ProjetilAtual->bAtivo)
	{
		Stats.Energia -= ProjetilAtual->EnergiaUtilizada * DeltaTime;

		if (Stats.Energia <= 0.0f)
		{
			Stats.Energia = 0.0f;
			UsarItem(true);
		}

	}

}

// Called to bind functionality to input
void AJogador::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AJogador::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	this->Stats.Vida -= dano;
	GerarCirculoDano(Hit);

	if (Stats.Vida <= 0)
	{
		JogadorMorreu();
	}
}

void AJogador::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil->IsValidLowLevelFast())
	{
		projetil->Stats = this->Stats;
	}
}

