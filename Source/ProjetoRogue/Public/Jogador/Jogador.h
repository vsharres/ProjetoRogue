// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Public/Itens/Item.h"
#include "Jogador.generated.h"

USTRUCT()
struct FJogadorStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float VidaMaxima;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float VelocidadeMov;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float TamanhoProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador Struct")
		float Vida;

	FORCEINLINE FJogadorStats& operator+=(const FItemStats& itemStats)
	{
		this->VidaMaxima += itemStats.IncrementaVidaMax;
		this->VelocidadeMov += itemStats.IncrementaVel;
		this->FireRate += itemStats.IncrementaFireRate;
		this->Range += itemStats.IncrementaRange;
		this->Dano += itemStats.IncrementaDano;
		this->TamanhoProjetil += itemStats.IncrementaParticula;
		this->Energia += itemStats.IncrementaEnergia;
		this->Vida += itemStats.IncrementaVida;

		return *this;
	}

	FORCEINLINE FJogadorStats& operator-=(const FItemStats& itemStats)
	{
		this->VidaMaxima -= itemStats.IncrementaVidaMax;
		this->VelocidadeMov -= itemStats.IncrementaVel;
		this->FireRate -= itemStats.IncrementaFireRate;
		this->Range -= itemStats.IncrementaRange;
		this->Dano -= itemStats.IncrementaDano;
		this->TamanhoProjetil -= itemStats.IncrementaParticula;
		this->Energia -= itemStats.IncrementaEnergia;
		this->Vida -= itemStats.IncrementaVida;

		return *this;
	}


	FJogadorStats(float vidMax = 100.0f, float velMov = 600.0f, float fireRate = 1.0f, float range =1000.0f, float dano =1.0f, float tamanhoProjet = 1.0f, int32 energia =0)
	{
		VidaMaxima = vidMax;
		VelocidadeMov = velMov;
		FireRate = fireRate;
		Range = range;
		Dano = dano;
		TamanhoProjetil = tamanhoProjet;
		Energia = energia;
		Vida = VidaMaxima;
	}

};


UCLASS()
class PROJETOROGUE_API AJogador : public ACharacter
{
	GENERATED_BODY()
	
public:

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<class AProjectil> ProjetilAtual;

	UPROPERTY()
		FName ProjetilSocket;

	// Sets default values for this character's properties
	AJogador();

	UFUNCTION()
		void AtualizarStats();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
