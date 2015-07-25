// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Interfaces/DanoInterface.h"
#include "Inimigo.generated.h"

UENUM(BlueprintType)
enum class ETipoInimigo :uint8
{
	BOT,
	TORRE,
	BOSS
};

UENUM(BlueprintType)
enum class ETipoAtaque :uint8
{
	MELEE,
	RANGE,
	AOE
};

USTRUCT()
struct FInimigoStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Vida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VidaAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelRotacao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Inimigo Struct")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Inimigo Struct")
		float TamanhoProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		ETipoInimigo Tipo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		ETipoAtaque TipoAtaque;

	FInimigoStats(float vida = 100.0f, float dano = 1.0f, float velRot = 1.0f, float range = 100.0f, float fireRate = 1.0f, float tamanho =1.0f, float velProjetil = 0.0f, int32 energia = 1, ETipoInimigo tipo = ETipoInimigo::BOT, ETipoAtaque ataque = ETipoAtaque::MELEE)
	{
		Vida = vida;
		VidaAtual = Vida;
		Dano = dano;
		VelRotacao = velRot;
		Range = range;
		FireRate = fireRate;
		TamanhoProjetil = tamanho;
		VelProjetil = velProjetil;
		Energia = energia;
		Tipo = tipo;
		TipoAtaque = ataque;
	}

};

//TODO
UCLASS(ABSTRACT,Blueprintable)
class PROJETOROGUE_API AInimigo : public APawn, public IDanoInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FInimigoStats Stats;

	UPROPERTY()
		bool bVivo;

	// Sets default values for this pawn's properties
	AInimigo();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void ReceberDano(const float& dano) override;

	UFUNCTION()
		bool EstaVivo();

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;



};
