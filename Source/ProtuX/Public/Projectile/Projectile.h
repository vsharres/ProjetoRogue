// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "Enemy.h"
#include "Projectile.generated.h"

/* Estrutura que representa os stats do projétil. */
USTRUCT()
struct FProjectileStats
{
	GENERATED_USTRUCT_BODY()
public:

	/* Intensidade da velocidade do projétil. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Speed;
	/* Dano a ser causado pelo projétil. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Damage;

	/* Construtor padrão. */
	FProjectileStats(float speed = 200.0f, float damage = 1.0f)
	{
		Speed = speed;
		Damage = damage;
	}

	/* Overload do operador para somar os stats do jogador aos stats do projétil.  */
	FORCEINLINE FProjectileStats& operator=(const FPlayerStats& playerStats)
	{
		this->Speed = playerStats.MuzzleSpeed;
		this->Damage = playerStats.Damage;

		return *this;
	}

	/* Overload do operador para somar os stats do inimigo aos stats do projétil.  */
	FORCEINLINE FProjectileStats& operator=(const FEnemyStats& enemyStats)
	{
		this->Speed = enemyStats.MuzzleSpeed;
		this->Damage = enemyStats.Damage;

		return *this;
	}


};

/* Estrutura que presenta os efeitos de impacto causados pelo projéil. */
USTRUCT()
struct FProjectileImpactEffect
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistem de partículas gerado no impacto. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* Effect;

	/* Som gerado no impacto. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* ImpactSoundFX;

	/* Material do decal gerado durante o impacto.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UMaterial* DecalMaterial;

	/* Tamanho do decal a ser gerado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalSize;

	/* Tempo de vida do decal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalHealth;

	/* Construtor padrão. */
	FProjectileImpactEffect()
	{
		Effect = NULL;
		ImpactSoundFX = NULL;
		DecalMaterial = NULL;
		DecalSize = 2.0f;
		DecalHealth = 3.0f;
	}
};

/* Estrutura que representa os efeitos gerados quando o projétil é atirado. */
USTRUCT()
struct FProjectileShootEffects
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistema de partículas gerado quando o projétil é atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* ShootFlash;

	/* Som gerado quando o projétil é atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* ShootSound;

	/* Construtor padrão.*/
	FProjectileShootEffects()
	{
		ShootFlash = NULL;
		ShootSound = NULL;
	}
};

/*
*	Classe derivada da classe AActor.
*	Classe que represeta o projétil atirado pelo jogador e pelos inimigos.
*/
UCLASS(ABSTRACT, Blueprintable)
class PROTUX_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

public:

	/* Booleano indicando se o projétil está ativo. O projétil apenas se move, é visível e causa dano quando ele estiver ativado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsActive;

	/* Stats do projétil. */
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		FProjectileStats Stats;

	/* Classe da animação da camera que será realizada quando o projétil é atirado. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Efeitos")
		TSubclassOf<UCameraShake> ShootCameraShake;

protected:

	/* Componente de movimentação do projétil, responsável pelas propriedades de movimentação.*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UProjectileMovementComponent* MovementComp;

	/* Componente de colisão do projétil. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		USphereComponent* CollisionComp;

	/* Componenete com o mesh do projétil. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UStaticMeshComponent* Mesh;

	/* Efeitos de impacto do projétil. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjectileImpactEffect ImpactFX;

	/* Efeitos de tiro do projétil. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjectileShootEffects ShootFX;

#pragma endregion


#pragma region CONSTRUTOR

public:
	/* Construtor padrão. */
	AProjectile(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUNÇÕES

	/*
	* Função de get do mesh do projétl.
	* @return - Ponteiro ao mesh do projétil.
	*/
	UFUNCTION(BlueprintPure, Category = "Component")
		UStaticMeshComponent* GetProjectileMesh();

	/*
	* Função de get do componente de movimentação do projétil.
	* @return - Ponteiro ao componente de movimentação.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Proj", Keywords = "Get Mov Proj"), Category = "Particula")
		UProjectileMovementComponent* GetMovComp();

	/*
	* Função para inicializar o projétil.
	* @param Inicializador - Ponteiro ao APawn responsável pela inicialização.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InicializarProj", Keywords = "Inicializar Projetil"), Category = "Projetil")
		void InitializeProjectile(ACharacter* initializer);

	/*
	* Função para ativar um projétil.
	* @param Localizacao - Vetor da localizao a onde o projétil será inicializado(Geralmente é ponto do canhao a onde sái o tiro).
	* @param Rotacao - Vetor de rotacao de inicialização do projetil (Geralmente está apontado para a posição da mira)
	* @param Inicializador - Ponteiro ao APawn responsável pela inicialização.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ativar Projetil", Keywords = "Ativar Projetil"), Category = "Projetil")
		void ActivateProjectile(const FVector& location, const FRotator& rotator, ACharacter* initializer); //MUDAR LOCATION PARA LOCALICAZAO e ROTATOR PARA ROTACAO

	/*
	* Função para desatovar um projétil.(Geralmente chamada quando um projétil ativo atinge um objeto)
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Desativar Projetil", Keywords = "Desativar Projetil"), Category = "Projetil")
		void DeactivateProjectile();

	/*
	* Função para gerar os efeitos de impacto.
	* @param Hit - Estrutura com as propriedades do ponto de colisão.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Impacto", Keywords = "Spawn Efeitos Impacto"), Category = "Projetil")
		void SpawnImpactFX(const FHitResult& Hit);

	/*
	* Função para gerar os efeitos de tiro do canhão.
	* @param Location - Local para gerar o efeito.
	* @param Rotator - Rotação do efeito.
	* @param Componente - Componente do ator para acoplar o efeito.
	* @param Nome -  Nome do bone do mesh a qual o efeito sera acoplado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Tiro", Keywords = "Spawn Efeitos Tiro"), Category = "Projetil")
		void SpawnShootFX(const FVector& location, const FRotator& rotator, USceneComponent* component, FName name);

	/* Override da função de inicialização do ator. */
	virtual void BeginPlay() override;

	/* Override do Tick do projétil. */
	virtual void Tick(float DeltaSeconds) override;

	/*
	* Override do Tick da sala.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Particula")
		void OnHitTarget();

	/*
	* Delegate de hit do projetil.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Hit", Keywords = "On Hit"), Category = "Particula")
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion



};
