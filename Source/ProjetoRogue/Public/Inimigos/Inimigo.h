// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "DanoInterface.h"
#include "Inimigo.generated.h"

/* Enumera��o do tipo de inimigo. */
UENUM(BlueprintType)
enum class ETipoInimigo :uint8
{
	DRONE,
	TORRE,
	BOT,
	BOSS
};

/* Enumera��o do tipo de ataque do inimigo. */
UENUM(BlueprintType)
enum class ETipoAtaque :uint8
{
	MELEE,
	RANGE,
	AOE
};

/* Estrutura dos stats do inimigo. */
USTRUCT()
struct FInimigoStats
{
	GENERATED_USTRUCT_BODY()

	/* Vida atual do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Vida;

	/* Vida m�xima do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VidaMax;

	/* Dano causado pelo inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Dano;

	/* Velocidade de rota��o do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelRotacao;

	/* Fire rate do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float FireRate;

	/* Precis�o do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Precisao;

	/* Velocidade do proj�til do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float VelProjetil;

	/* Tipo de ataque do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		ETipoAtaque TipoAtaque;

	/* Construtor padr�o. */
	FInimigoStats(float vida = 100.0f, float dano = 1.0f, float velRot = 1.0f, float fireRate = 1.0f, float precisao = 1.0f, float velProjetil = 0.0f, ETipoAtaque ataque = ETipoAtaque::MELEE)
	{
		Vida = vida;
		VidaMax = vida;
		Dano = dano;
		VelRotacao = velRot;
		FireRate = fireRate;
		Precisao = precisao;
		VelProjetil = velProjetil;
		TipoAtaque = ataque;
	}

};

/* Classe que representa os inimigos controlados pela AI. */
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AInimigo : public ACharacter, public IDanoInterface
{
	GENERATED_BODY()

#pragma region Propriedades
protected:

	/* Tipo do inimigos. */
	UPROPERTY(EditDefaultsOnly, Category = "Inimigo")
		ETipoInimigo TipoInimigo;

	/* N�mero de pickups gerado pelo inimigo em morte. */
	UPROPERTY(EditAnywhere, Category = "PickUp")
		int32 NumPickUps;
	/* Chance de spawn pickups de vida. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnVida;
	/* Chance de spawn pickups de energia. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnEnergia;
	/* Chance de spawn pickups de Scrap. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ChanceSpawnScrap;

	/* Clase do objeto de pickup de energia. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpEnergia> PickUpEnergiaClass;

	/* Clase do objeto de pickup de vida. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpVida> PickUpVidaClass;

	/* Clase do objeto de pickup de Scrap. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpMoeda> PickUpScrapClass;

	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class APickUpItem> PickUpItemClass;


public:

	/* Stats do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FInimigoStats Stats;

	/* Ponteiro a sala pai do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TWeakObjectPtr<class ASala> SalaPai;

	/* Array com as �ltimas velocidades do jogador, usado para a mira do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador")
		TArray<FVector> UltimasVelJogador;

	/* Booleano indicando quando o inimigo est� atacando. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bEstaAtacando;

	/* Booleano indicando quando o inimigo est� Morrendo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bEstaMorrendo;
#pragma endregion Propriedades

#pragma region Construtor
/* Construtor Padr�o */
	AInimigo(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Fun��es
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/*
	* Fun��o de Get da posi��o de tiro do inimigo.
	* @return FVector da posi��o de tiro.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		FVector GetPosicaoTiro();

	/*
	* Fun��o de Get da rota��o de tiro do inimigo.
	* @return FRotator da rota��os de tiro.
	*/
	UFUNCTION(BlueprintPure, Category = Mesh)
		FRotator GetDirecaoTiro();

	/*
	* Fun��o ed interface para receber dano.
	* @param dano - float de dano.
	* @param prjetil - ponteiro do projetil que causou dano.
	* @param Hit - Resultados do hit do proj�til.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inimigos")
		virtual void ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit) override;

	/*
	* Fun��o para checar a vida do inimigo
	* @return booleano indicando se o inimigo est� vivo.
	*/
	UFUNCTION()
		bool EstaVivo();

	/*
	* Fun��o para fazer o spawn do pickup quando o inimigo morre.
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
		void SpawnPickUp();

	/*
	* Evento disparado para fazer um flash no material do inimigo.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Inimigo")
		void FlashDano();

	/*
	* Evento disparado quando o inimigo morreu
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Inimigo)
		void InimigoMorreu();
	/*
	* Fun��o de interface para aplicar os stats do inimigo no proj�til
	* @param projetil - Projetil que tem stats aplicados.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void AplicarStatsProjetil(AProjectil* projetil) override;

#pragma endregion Fun��es

};
