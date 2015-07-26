// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Public/Itens/Item.h"
#include "Public/Interfaces/DanoInterface.h"
#include "Public/Interfaces/DebugInterface.h"
#include "Jogador.generated.h"


USTRUCT()
struct FJogadorStats
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0"), Category = "Jogador Struct")
		float Vida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "100.0"), Category = "Jogador Struct")
		float VidaMaxima;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0"), Category = "Jogador Struct")
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "100.0"), Category = "Jogador Struct")
		float VelocidadeMov;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0"), Category = "Jogador Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0"), Category = "Jogador Struct")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0"), Category = "Jogador Struct")
		float TamanhoProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "100.0"), Category = "Jogador Struct")
		float VelProjetil;


	FORCEINLINE FJogadorStats& operator+=(const FItemStats& itemStats)
	{
		this->VidaMaxima += itemStats.IncrementaVidaMax;
		this->VelocidadeMov += itemStats.IncrementaVel;
		this->FireRate += itemStats.IncrementaFireRate;
		this->Dano += itemStats.IncrementaDano;
		this->TamanhoProjetil += itemStats.IncrementaTamanho;
		this->VelProjetil += itemStats.IncrementaVelProjetil;
		this->Energia += itemStats.IncrementaEnergia;
		this->Vida += itemStats.IncrementaVida;

		return *this;
	}

	FORCEINLINE FJogadorStats& operator-=(const FItemStats& itemStats)
	{
		this->VidaMaxima -= itemStats.IncrementaVidaMax;
		this->VelocidadeMov -= itemStats.IncrementaVel;
		this->FireRate -= itemStats.IncrementaFireRate;
		this->Dano -= itemStats.IncrementaDano;
		this->TamanhoProjetil -= itemStats.IncrementaTamanho;
		this->VelProjetil -= itemStats.IncrementaVelProjetil;
		this->Energia -= itemStats.IncrementaEnergia;
		this->Vida -= itemStats.IncrementaVida;

		return *this;
	}


	FJogadorStats(float vidMax = 100.0f, float velMov = 600.0f, float fireRate = 1.0f, float dano = 1.0f, float tamanhoProjet = 1.0f, float velProjetil = 100.0f, int32 energia = 0)
	{
		VidaMaxima = vidMax;
		VelocidadeMov = velMov;
		FireRate = fireRate;
		Dano = dano;
		TamanhoProjetil = tamanhoProjet;
		VelProjetil = velProjetil;
		Energia = energia;
		Vida = VidaMaxima;
	}

};


UCLASS()
class PROJETOROGUE_API AJogador : public ACharacter, public IDanoInterface, public IDebugInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool bDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FJogadorStats Stats;

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

	//PROJETIL

	UPROPERTY()
		int32 NumProjeteis;

	UPROPERTY(EditDefaultsOnly, Category = "Projetil")
		TSubclassOf<class UItemProjetil> ProjetilInicial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		UItemProjetil* ProjetilAtual;

	UPROPERTY()
		FName ProjetilSocket;

	// Sets default values for this character's properties
	AJogador();

	UFUNCTION()
		void AtualizarStats();

	UFUNCTION()
		bool EstaVivo();

	//INTERFACES

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void ReceberDano(const float& dano) override;

	virtual void Debug() override;

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		void Atirar();


	UFUNCTION()
		void ItemCooldown(float DeltaTime);





};
