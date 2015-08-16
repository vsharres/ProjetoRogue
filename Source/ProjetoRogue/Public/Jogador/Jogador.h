// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DanoInterface.h"
#include "DebugInterface.h"
#include "Item.h"
#include "Jogador.generated.h"

const float VIDAMAX_MAX = 500.0F;
const float VIDAMAX_MIN = 50.0f;
const int32 ENERGIA_MAX = 300;
const int32 ENERGIA_MIN = 0;
const float VELOCIDADEMOV_MAX = 1800.0f;
const float VELOCIDADEMOV_MIN = 600.0f;
const float DANO_MAX = 50.0f;
const float DANO_MIN = 5;
const float FIRERATE_MAX = 1.0f;
const float FIRERATE_MIN = 0.005f;
const float TAMANHO_MAX = 0.6f;
const float TAMANHAO_MIN = 0.1f;
const float VELOCIDADEPROJ_MAX = 6000.0f;
const float VELOCIDADEPROJ_MIN = 1000.f;



USTRUCT()
struct FJogadorStats
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "50.0"), Category = "Jogador Struct")
		float Vida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "50.0"), Category = "Jogador Struct")
		float VidaMaxima;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0"), Category = "Jogador Struct")
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0"), Category = "Jogador Struct")
		int32 EnergiaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "600.0"), Category = "Jogador Struct")
		float VelocidadeMov;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "5.0"), Category = "Jogador Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.04"), Category = "Jogador Struct")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1"), Category = "Jogador Struct")
		float TamanhoProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "250.0"), Category = "Jogador Struct")
		float VelProjetil;


	FORCEINLINE FJogadorStats& operator+=(const FItemStats& itemStats)
	{
		this->VidaMaxima += itemStats.IncrementaVidaMax;
		this->EnergiaMax += itemStats.IncrementaEnergiaMax;
		this->VelocidadeMov += itemStats.IncrementaVel;
		this->FireRate += itemStats.IncrementaFireRate;
		this->Dano += itemStats.IncrementaDano;
		this->TamanhoProjetil += itemStats.IncrementaTamanho;
		this->VelProjetil += itemStats.IncrementaVelProjetil;

		AdicionarEnergia(itemStats.IncrementaEnergia);
		AdicionarVida(itemStats.IncrementaVida);

		ChecarValores();

		return *this;
	}

	FORCEINLINE FJogadorStats& operator-=(const FItemStats& itemStats)
	{
		this->VidaMaxima -= itemStats.IncrementaVidaMax;
		this->EnergiaMax -= itemStats.IncrementaEnergiaMax;
		this->VelocidadeMov -= itemStats.IncrementaVel;
		this->FireRate -= itemStats.IncrementaFireRate;
		this->Dano -= itemStats.IncrementaDano;
		this->TamanhoProjetil -= itemStats.IncrementaTamanho;
		this->VelProjetil -= itemStats.IncrementaVelProjetil;
		AdicionarEnergia(-itemStats.IncrementaEnergia);
		AdicionarVida(-itemStats.IncrementaVida);

		ChecarValores();

		return *this;
	}

	FORCEINLINE void ChecarValores()
	{
		if (VidaMaxima > VIDAMAX_MAX)
		{
			VidaMaxima = VIDAMAX_MAX;
		}
		else if (VidaMaxima < VIDAMAX_MIN)
		{
			VidaMaxima = VIDAMAX_MIN;
		}

		if (VelocidadeMov > VELOCIDADEMOV_MAX)
		{
			VelocidadeMov = VELOCIDADEMOV_MAX;
		}
		else if (VelocidadeMov < VELOCIDADEMOV_MIN)
		{
			VelocidadeMov = VELOCIDADEMOV_MIN;
		}

		if (FireRate > FIRERATE_MAX)
		{
			FireRate = FIRERATE_MAX;
		}
		else if (FireRate < FIRERATE_MIN)
		{
			FireRate = FIRERATE_MIN;
		}

		if (Dano > DANO_MAX)
		{
			Dano = DANO_MAX;
		}
		else if (Dano < DANO_MIN)
		{
			Dano = DANO_MIN;
		}

		if (TamanhoProjetil > TAMANHO_MAX)
		{
			TamanhoProjetil = TAMANHO_MAX;
		}
		else if (TamanhoProjetil < TAMANHAO_MIN)
		{
			TamanhoProjetil = TAMANHAO_MIN;
		}

		if (VelProjetil > VELOCIDADEPROJ_MAX)
		{
			VelProjetil = VELOCIDADEPROJ_MAX;
		}
		else if (VelProjetil < VELOCIDADEPROJ_MIN)
		{
			VelProjetil = VELOCIDADEPROJ_MIN;
		}

		if (EnergiaMax > ENERGIA_MAX)
		{
			EnergiaMax = ENERGIA_MAX;
		}
		else if (EnergiaMax < ENERGIA_MIN)
		{
			EnergiaMax = ENERGIA_MIN;
		}

	}

	FORCEINLINE void AdicionarVida(float vidaAdicionada)
	{
		Vida += vidaAdicionada;

		if (Vida > VidaMaxima)
		{
			Vida = VidaMaxima;
		}
		else if (Vida < 0)
		{
			Vida = 0;
		}

	}

	FORCEINLINE void AdicionarEnergia(int32 energidaAdicionada)
	{
		Energia += energidaAdicionada;

		if (Energia > EnergiaMax)
		{
			Energia = EnergiaMax;
		}
		else if (Energia < 0)
		{
			Energia = 0;
		}
	}

	FORCEINLINE void SetStats(const FJogadorStats& stats)
	{
		this->Vida = stats.Vida;
		this->VidaMaxima = stats.VidaMaxima;
		this->Energia = stats.Energia;
		this->EnergiaMax = stats.EnergiaMax;
		this->VelocidadeMov = stats.VelocidadeMov;
		this->Dano = stats.Dano;
		this->FireRate = stats.FireRate;
		this->TamanhoProjetil = stats.TamanhoProjetil;
		this->VelProjetil = stats.VelProjetil;
	}

	FJogadorStats(float vidMax = 100.0f, float velMov = 600.0f, float fireRate = 0.05f, float dano = 5.0f, float tamanhoProjet = 0.3f, float velProjetil = 1500.0f, int32 energia = 100)
	{
		VidaMaxima = vidMax;
		VelocidadeMov = velMov;
		FireRate = fireRate;
		Dano = dano;
		TamanhoProjetil = tamanhoProjet;
		VelProjetil = velProjetil;
		Energia = energia;
		EnergiaMax = Energia;
		Vida = VidaMaxima;
	}

	FJogadorStats(const FJogadorStats& Outro)
	{
		VidaMaxima = Outro.VidaMaxima;
		VelocidadeMov = Outro.VelocidadeMov;
		FireRate = Outro.FireRate;
		Dano = Outro.Dano;
		TamanhoProjetil = Outro.TamanhoProjetil;
		VelProjetil = Outro.VelProjetil;
		Energia = Outro.Energia;
		EnergiaMax = Outro.EnergiaMax;
		Vida = Outro.Vida;
	}

};


UCLASS()
class PROJETOROGUE_API AJogador : public ACharacter, public IDanoInterface, public IDebugInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nome")
		FString Nome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool bDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FJogadorStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moedas")
		int32 Moedas;

	//ITENS

	UPROPERTY(BlueprintReadWrite, Category = "Item")
		float CooldownAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "5.0"), Category = "Item")
		float TempoCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1", UIMax = "10.0"), Category = "Item")
		float CooldDownRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bPossuiChave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UItemAtivo* ItemAtivoAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<class UItemPassivo*> ItensPassivos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bItemEncontrado;

	//PROJETIL

	UPROPERTY()
		int32 NumProjeteis;

	UPROPERTY(EditDefaultsOnly, Category = "Projetil")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		UItemProjetil* ProjetilAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TArray<AProjectil*> ProjetilPool;

	UPROPERTY()
		FName ProjetilSocket;

	// Sets default values for this character's properties
	AJogador(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category ="Jogador")
		void InicializarJogador();

	UFUNCTION(BlueprintCallable, Category = "Nome")
		void GerarNome(int32 index);

	UFUNCTION()
		void AtualizarPropriedadesComStats();

	UFUNCTION()
		void InicializarProjetil();

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		void GerarProjetilPool();

	UFUNCTION()
		bool EstaVivo();

	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarVida(float vida);

	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarEnerngia(int32 energia);

	UFUNCTION(BlueprintCallable, Category = "Jogador")
		void AdicionarMoedas(int32 valor);

	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void SalvarJogador();

	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void CarregarJogador();

	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void NovoJogador();

	//INTERFACES

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Jogador")
	virtual void ReceberDano(const float& dano) override;

	virtual void Debug() override;

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Projetil")
		virtual void Atirar();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Jogador Morreu", Keywords = "Jogador Morreu"), Category = "Jogador")
		virtual void JogadorMorreu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar PopUp", Keywords = "Gerar PopUp"), Category = "Jogador")
		virtual void GerarPopUp(float dano, AInimigo* alvo);

	UFUNCTION()
		void ItemCooldown(float DeltaTime);





};
