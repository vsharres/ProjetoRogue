// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Jogador.h"
#include "Projectil.h"
#include "ItemPassivo.h"
#include "ItemProjetil.h"

AJogador::AJogador(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Inicializando propriedades
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

	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex) == false ? UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex) : NULL;

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->bNovoJogo || gameMode->bNaoSalvar) //caso nao seja um novo novo, carregar o jogador
	{
		NovoJogador();
	}
	else
	{
		CarregarJogador();
	}

	InicializarProjetil(false); //inicializar o projetil.
}

void AJogador::GerarNome(int32 index)
{
	FString num;

	int32 temp = index;

	while (temp != 0 && temp <= 999) //gerar o nome da versão em numeral romanos
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
	GetCharacterMovement()->MaxWalkSpeed = Stats.VelocidadeMov; //atualizar a velocidade de movimentação do personagem do jogador com os stats
}

bool AJogador::EstaVivo()
{
	if (Stats.Vida > 0.01) //checar vida
	{
		return true;
	}

	return false;
}

void AJogador::AdicionarVida(float vida)
{
	this->Stats.AdicionarVida(vida);

}

void AJogador::AdicionarEnerngia(float energia)
{
	Stats.AdicionarEnergia(energia);
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

	//Criando objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//salvar as propriedades do jogador
		SaveInst->bNovoJogo = false;
		SaveInst->Stats.SetStats(this->Stats);
		SaveInst->Scrap = this->Moedas;
		SaveInst->bPossuiChave = this->bPossuiChave;

		//Salvando transform do jogador
		SaveInst->JogadorLocation = this->GetActorLocation();
		SaveInst->JogadorRotation = this->GetActorRotation();

		if (ProjetilEncontrado) //salvar referência ao asset do projetil encontrado
		{
			SaveInst->ProjetilEncontrado_Referencia = FStringAssetReference(this->ProjetilEncontrado).ToString();
		}

		SaveInst->bItemEncontrado = this->bItemEncontrado;

		SaveInst->ItensPassivos_Referencias.Empty();
		for (const auto& item : ItensPassivos) //salvar as referências aos assets dos itens passivos.
		{

			SaveInst->ItensPassivos_Referencias.Add(FStringAssetReference(item->GetClass()).ToString());
		}

		//Salvar jogador.
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void AJogador::CarregarJogador()
{
	//Criar objeto de save
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//Carregando propriedades
		GerarNome(SaveInst->NumJogos);
		this->Stats.SetStats(SaveInst->Stats);
		this->Moedas = SaveInst->Scrap;
		
		if (SaveInst->bContinuarJogo)
		{
			//Carregando transform do jogador
			this->SetActorLocation(SaveInst->JogadorLocation);
			this->SetActorRotation(SaveInst->JogadorRotation);
			this->bPossuiChave = SaveInst->bPossuiChave;
		}

		if (!SaveInst->ProjetilEncontrado_Referencia.IsEmpty()) //criando o projetil encontrando
		{
			UItemProjetil* itemProjetil = NewObject<UItemProjetil>(this, StaticLoadClass(UItemProjetil::StaticClass(), NULL, *SaveInst->ProjetilEncontrado_Referencia));

			if (itemProjetil)
			{
				this->ProjetilEncontrado = itemProjetil->GetClass();
			}
		}


		if (SaveInst->ItensPassivos_Referencias.Num() > 0) //criando os itens passivos encontrados
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
	//Criando um novo jogador
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		GerarNome(SaveInst->NumJogos); //isar o número de jogos para determinar o número da versão do prototipo
	}

}

void AJogador::UsarItem(bool bDesativar)
{
	if (ProjetilEncontrado->IsValidLowLevelFast()) //checar que o projetil encontrado é valido
	{
		InicializarProjetil(bDesativar); //inicializar o projetil e atulizar o mesh do canhão
		AtualizarMesh();
	}
}

void AJogador::InicializarProjetil(bool bDesativar)
{
	if (ProjetilAtual ==  NULL && !bDesativar) //checar que o projetil atual é valido e não esta sendo desativado
	{
		//Inicializar o projetil atual como o projetil inicial do jogo.
		ProjetilAtual = NewObject<UItemProjetil>(this, ProjetilInicial);
		ProjetilAtual->InicializarItem(this);
		GerarProjetilPool();

	}
	else if (bDesativar)
	{
		//Desativar o item ativo e reverter o projetil ao projetil inicial do jogo.
		ProjetilAtual->DesativarItem();
		ProjetilAtual->RemoverItem();
		ProjetilAtual = NewObject<UItemProjetil>(this, ProjetilInicial);
		ProjetilAtual->InicializarItem(this);
		GerarProjetilPool();
	}
	else
	{
		//Ativar o item ativo e setar o projetil atual como o projetil do item ativo.
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
	if (ProjetilPool.Num() > 0) //Deletar os projeteis que já estão no array.
	{
		ProjetilPool.Empty();
	}

	for (int32 index = 0; index < NumProjeteis; index++) //criar os projeteis do pool
	{
		FVector tiroPos = FVector(0, 0, 1000);

		//Spawn do projétil
		AProjectil* Tiro = GetWorld()->SpawnActor<AProjectil>(ProjetilAtual->Projetil, tiroPos, GetControlRotation());

		if (Tiro->IsValidLowLevelFast())
		{
			Tiro->Instigator = this; //Jogador é o responsável pelo dano do jogador.
			Tiro->SetActorHiddenInGame(true); //Esconder o projetil
			Tiro->Instigator = this;
			ProjetilPool.Add(Tiro); //Adicionar ao pool
		}
	}

	//pegar a cor do projetil atual e salvar na variável projetilCor
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

void AJogador::ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit)
{
	this->Stats.Vida -= dano; //receber o dano
	GerarCirculoDano(Hit); //gerar o círculo de dano.

	if (Stats.Vida <= 0) //se a vida for menor do que 0, o jogador morreu
	{
		JogadorMorreu();
	}
}

void AJogador::AplicarStatsProjetil(AProjectil* projetil)
{
	if (projetil->IsValidLowLevelFast())
	{
		projetil->Stats = this->Stats; //aplicar os stats do jogador ao projétil.
	}
}

