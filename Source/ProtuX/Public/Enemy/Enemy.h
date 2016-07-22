// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "DamageInterface.h"
#include "Enemy.generated.h"

/* Enumeração do tipo de inimigo. */
UENUM(BlueprintType)
enum class EEnemyType :uint8
{
	DRONE,
	TOWER,
	BOT,
	BOSS
};

/* Enumeração do tipo de ataque do inimigo. */
UENUM(BlueprintType)
enum class EAttackType :uint8
{
	MELEE,
	RANGE,
	AOE
};

/* Estrutura dos stats do inimigo. */
USTRUCT()
struct FEnemyStats
{
	GENERATED_USTRUCT_BODY()

	/* Vida atual do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Health;

	/* Vida máxima do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float MaxHealth;

	/* Dano causado pelo inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Damage;

	/* Velocidade de rotação do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float RotationSpeed;

	/* Fire rate do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float FireRate;

	/* Precisão do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float Accuracy;

	/* Velocidade do projétil do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		float MuzzleSpeed;

	/* Tipo de ataque do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		EAttackType AttackType;

	/* Construtor padrão. */
	FEnemyStats(float heatlh = 100.0f, float damage = 1.0f, float rotSpeed = 1.0f, float fireRate = 1.0f, float accurary = 1.0f, float muzzleSpeed = 0.0f, EAttackType attackType = EAttackType::MELEE)
	{
		Health = heatlh;
		MaxHealth = heatlh;
		Damage = damage;
		RotationSpeed = rotSpeed;
		FireRate = fireRate;
		Accuracy = accurary;
		MuzzleSpeed = muzzleSpeed;
		AttackType = attackType;
	}

};

/* Classe que representa os inimigos controlados pela AI. */
UCLASS(ABSTRACT, Blueprintable)
class PROTUX_API AEnemy : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

#pragma region Propriedades
protected:

	/* Tipo do inimigos. */
	UPROPERTY(EditDefaultsOnly, Category = "Inimigo")
		EEnemyType EnemyType;

	/* Número de pickups gerado pelo inimigo em morte. */
	UPROPERTY(EditAnywhere, Category = "PickUp")
		int32 PickUpNumber;

	/* Chance de spawn pickups de vida. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float HealthPickUpSpawnChance;

	/* Chance de spawn pickups de energia. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float EnergyPickUpSpawnChance;

	/* Chance de spawn pickups de Scrap. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "100.0"), Category = "PickUp")
		float ScrapPickUpSpawnChance;

	/* Clase do objeto de pickup de energia. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AEnergyPickUp> EnergyPickUpClass;

	/* Clase do objeto de pickup de vida. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AHealthPickUp> HealthPickUpClass;

	/* Clase do objeto de pickup de Scrap. */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AScrapPickUP> ScrapPickUpClass;

	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
		TSubclassOf<class AItemPickUp> ItemPickUpClass;


public:

	/* Stats do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FEnemyStats Stats;

	/* Ponteiro a sala pai do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TWeakObjectPtr<class ARoom> ParentRoom;

	/* Array com as últimas velocidades do jogador, usado para a mira do inimigo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jogador")
		TArray<FVector> LastPlayerVelocity;

	/* Booleano indicando quando o inimigo está atacando. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bIsAttacking;

	/* Booleano indicando quando o inimigo está Morrendo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
		bool bIsDying;
#pragma endregion Propriedades

#pragma region Construtor
/* Construtor Padrão */
	AEnemy(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Funções

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	/*
	* Função de Get da posição de tiro do inimigo.
	* @return FVector da posição de tiro.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		FVector GetFiringPos();

	/*
	* Função de Get da rotação de tiro do inimigo.
	* @return FRotator da rotaçãos de tiro.
	*/
	UFUNCTION(BlueprintPure, Category = Mesh)
		FRotator GetFiringDir();

	/*
	* Função ed interface para receber dano.
	* @param dano - float de dano.
	* @param prjetil - ponteiro do projetil que causou dano.
	* @param Hit - Resultados do hit do projétil.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inimigos")
		virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	/*
	* Função para checar a vida do inimigo
	* @return booleano indicando se o inimigo está vivo.
	*/
	UFUNCTION()
		bool IsAlive();

	UFUNCTION()
		virtual void CalculateStats(int32 currentLevel);

	/*
	* Função para fazer o spawn do pickup quando o inimigo morre.
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
		void SpawnPickUp();

	/*
	* Evento disparado para fazer um flash no material do inimigo.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Inimigo")
		void FlashDamage();

	/*
	* Evento disparado quando o inimigo morreu
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Inimigo)
		void OnEnemyDeath();
	/*
	* Função de interface para aplicar os stats do inimigo no projétil
	* @param projetil - Projetil que tem stats aplicados.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projetil")
		virtual void ApplyProjectileStats(AProjectile* projectile) override;

#pragma endregion Funções

};
