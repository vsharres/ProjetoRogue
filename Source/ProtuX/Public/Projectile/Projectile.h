// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "Enemy.h"
#include "Projectile.generated.h"

/* Estrutura que representa os stats do proj�til. */
USTRUCT()
struct FProjectileStats
{
	GENERATED_USTRUCT_BODY()
public:

	/* Intensidade da velocidade do proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Speed;
	/* Dano a ser causado pelo proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Damage;

	/* Construtor padr�o. */
	FProjectileStats(float speed = 200.0f, float damage = 1.0f)
	{
		Speed = speed;
		Damage = damage;
	}

	/* Overload do operador para somar os stats do jogador aos stats do proj�til.  */
	FORCEINLINE FProjectileStats& operator=(const FPlayerStats& playerStats)
	{
		this->Speed = playerStats.MuzzleSpeed;
		this->Damage = playerStats.Damage;

		return *this;
	}

	/* Overload do operador para somar os stats do inimigo aos stats do proj�til.  */
	FORCEINLINE FProjectileStats& operator=(const FEnemyStats& enemyStats)
	{
		this->Speed = enemyStats.MuzzleSpeed;
		this->Damage = enemyStats.Damage;

		return *this;
	}


};

/* Estrutura que presenta os efeitos de impacto causados pelo proj�il. */
USTRUCT()
struct FProjectileImpactEffect
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistem de part�culas gerado no impacto. */
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

	/* Construtor padr�o. */
	FProjectileImpactEffect()
	{
		Effect = NULL;
		ImpactSoundFX = NULL;
		DecalMaterial = NULL;
		DecalSize = 2.0f;
		DecalHealth = 3.0f;
	}
};

/* Estrutura que representa os efeitos gerados quando o proj�til � atirado. */
USTRUCT()
struct FProjectileShootEffects
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistema de part�culas gerado quando o proj�til � atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* ShootFlash;

	/* Som gerado quando o proj�til � atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* ShootSound;

	/* Construtor padr�o.*/
	FProjectileShootEffects()
	{
		ShootFlash = NULL;
		ShootSound = NULL;
	}
};

/*
*	Classe derivada da classe AActor.
*	Classe que represeta o proj�til atirado pelo jogador e pelos inimigos.
*/
UCLASS(ABSTRACT, Blueprintable)
class PROTUX_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

public:

	/* Booleano indicando se o proj�til est� ativo. O proj�til apenas se move, � vis�vel e causa dano quando ele estiver ativado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsActive;

	/* Stats do proj�til. */
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		FProjectileStats Stats;

	/* Classe da anima��o da camera que ser� realizada quando o proj�til � atirado. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Efeitos")
		TSubclassOf<UCameraShake> ShootCameraShake;

protected:

	/* Componente de movimenta��o do proj�til, respons�vel pelas propriedades de movimenta��o.*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UProjectileMovementComponent* MovementComp;

	/* Componente de colis�o do proj�til. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		USphereComponent* CollisionComp;

	/* Componenete com o mesh do proj�til. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UStaticMeshComponent* Mesh;

	/* Efeitos de impacto do proj�til. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjectileImpactEffect ImpactFX;

	/* Efeitos de tiro do proj�til. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjectileShootEffects ShootFX;

#pragma endregion


#pragma region CONSTRUTOR

public:
	/* Construtor padr�o. */
	AProjectile(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUN��ES

	/*
	* Fun��o de get do mesh do proj�tl.
	* @return - Ponteiro ao mesh do proj�til.
	*/
	UFUNCTION(BlueprintPure, Category = "Component")
		UStaticMeshComponent* GetProjectileMesh();

	/*
	* Fun��o de get do componente de movimenta��o do proj�til.
	* @return - Ponteiro ao componente de movimenta��o.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Proj", Keywords = "Get Mov Proj"), Category = "Particula")
		UProjectileMovementComponent* GetMovComp();

	/*
	* Fun��o para inicializar o proj�til.
	* @param Inicializador - Ponteiro ao APawn respons�vel pela inicializa��o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InicializarProj", Keywords = "Inicializar Projetil"), Category = "Projetil")
		void InitializeProjectile(ACharacter* initializer);

	/*
	* Fun��o para ativar um proj�til.
	* @param Localizacao - Vetor da localizao a onde o proj�til ser� inicializado(Geralmente � ponto do canhao a onde s�i o tiro).
	* @param Rotacao - Vetor de rotacao de inicializa��o do projetil (Geralmente est� apontado para a posi��o da mira)
	* @param Inicializador - Ponteiro ao APawn respons�vel pela inicializa��o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ativar Projetil", Keywords = "Ativar Projetil"), Category = "Projetil")
		void ActivateProjectile(const FVector& location, const FRotator& rotator, ACharacter* initializer); //MUDAR LOCATION PARA LOCALICAZAO e ROTATOR PARA ROTACAO

	/*
	* Fun��o para desatovar um proj�til.(Geralmente chamada quando um proj�til ativo atinge um objeto)
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Desativar Projetil", Keywords = "Desativar Projetil"), Category = "Projetil")
		void DeactivateProjectile();

	/*
	* Fun��o para gerar os efeitos de impacto.
	* @param Hit - Estrutura com as propriedades do ponto de colis�o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Impacto", Keywords = "Spawn Efeitos Impacto"), Category = "Projetil")
		void SpawnImpactFX(const FHitResult& Hit);

	/*
	* Fun��o para gerar os efeitos de tiro do canh�o.
	* @param Location - Local para gerar o efeito.
	* @param Rotator - Rota��o do efeito.
	* @param Componente - Componente do ator para acoplar o efeito.
	* @param Nome -  Nome do bone do mesh a qual o efeito sera acoplado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Tiro", Keywords = "Spawn Efeitos Tiro"), Category = "Projetil")
		void SpawnShootFX(const FVector& location, const FRotator& rotator, USceneComponent* component, FName name);

	/* Override da fun��o de inicializa��o do ator. */
	virtual void BeginPlay() override;

	/* Override do Tick do proj�til. */
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
