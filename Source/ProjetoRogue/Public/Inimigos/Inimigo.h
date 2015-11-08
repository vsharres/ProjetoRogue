// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "DanoInterface.h"
#include "Inimigo.generated.h"


UENUM(BlueprintType)
enum class ETipoInimigo :uint8
{
	DRONE,
	TORRE,
	BOT,
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
		float VidaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelRotacao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Precisao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelProjetil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		ETipoAtaque TipoAtaque;

	FInimigoStats(float vida = 100.0f, float dano = 1.0f, float velRot = 1.0f, float fireRate = 1.0f, float precisao = 1.0f, float velProjetil = 0.0f, int32 energia = 1, ETipoAtaque ataque = ETipoAtaque::MELEE)
	{
		Vida = vida;
		VidaMax = vida;
		Dano = dano;
		VelRotacao = velRot;
		FireRate = fireRate;
		Precisao = precisao;
		VelProjetil = velProjetil;
		Energia = energia;
		TipoAtaque = ataque;
	}

};

//TODO
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AInimigo : public ACharacter, public IDanoInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Inimigo")
		ETipoInimigo TipoInimigo;

	UPROPERTY(EditAnywhere, Category = "PickUp")
		int32 NumPickUps;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnVida;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnEnergia;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnMoeda;

	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpEnergia> PickUpEnergiaClass;

	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpVida> PickUpVidaClass;

	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpMoeda> PickUpMoedaClass;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FInimigoStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TWeakObjectPtr<class ASala> SalaPai;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador")
		TArray<FVector> UltimasVelJogador;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bEstaAtacando;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bEstaMorrendo;

	// Sets default values for this pawn's properties
	AInimigo(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category = "Mesh")
		FVector GetPosicaoTiro();

	UFUNCTION(BlueprintPure, Category = Mesh)
		FRotator GetDirecaoTiro();

	UFUNCTION(BlueprintCallable, Category = "Inimigos")
		virtual void ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit) override;

	UFUNCTION()
		bool EstaVivo();

	UFUNCTION(BlueprintCallable, Category = PickUp)
		void SpawnPickUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inimigo")
		void FlashDano();

	UFUNCTION(BlueprintImplementableEvent, Category = Inimigo)
		void InimigoMorreu();

	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;



};
