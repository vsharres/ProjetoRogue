// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Projectil.generated.h"

USTRUCT()
struct FProjetilStats
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float TiroDesvio;


	FProjetilStats(float velocidade = 200.0f, float dano = 1.0f, float desvio =1.0f)
	{
		Velocidade = velocidade;
		Dano = dano;
		TiroDesvio = desvio;
	}

	FORCEINLINE FProjetilStats& operator=(const FJogadorStats& statsJogador)
	{
		this->Velocidade = statsJogador.VelProjetil;
		this->Dano = statsJogador.Dano;

		return *this;
	}

	FORCEINLINE FProjetilStats& operator=(const FInimigoStats& statsInimigo)
	{
		this->Velocidade = statsInimigo.VelProjetil;
		this->Dano = statsInimigo.Dano;

		return *this;
	}


};

USTRUCT()
struct FProjetilImpactoEfeito
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* Efeito;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* SomImpacto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UMaterial* DecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Tamanho;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalVida;

	FProjetilImpactoEfeito()
	{
		Efeito = NULL;
		SomImpacto = NULL;
		DecalMaterial = NULL;
		Tamanho = 2.0f;
		DecalVida = 3.0f;
	}
};

USTRUCT()
struct FProjetilAtirarEfeitos
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* TiroFlash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* SomTiro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Tamanho;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalVida;

	FProjetilAtirarEfeitos()
	{
		TiroFlash = NULL;
		SomTiro = NULL;
		Tamanho = 1.0f;
		DecalVida = 2.0f;
	}
};

//TODO
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bAtivo;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
		FProjetilStats Stats;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Efeitos")
		TSubclassOf<UCameraShake> FireCameraShake;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UProjectileMovementComponent* CompMovimentacao;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		USphereComponent* CompCollisao;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjetilImpactoEfeito ImapctoEfeitos;


public:
	// Sets default values for this actor's properties
	AProjectil(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Component")
		UStaticMeshComponent* GetProjetilMesh();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Proj", Keywords = "Get Mov Proj"), Category = "Particula")
		UProjectileMovementComponent* GetMovProjetil();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InicializarProj", Keywords = "Inicializar Projetil"), Category = "Projetil")
		void InicializarProjetil(AActor* Inicializador);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ativar Projetil", Keywords = "Ativar Projetil"), Category = "Projetil")
		void AtivarProjetil(const FVector& Location, const FRotator& Rotator, APawn* Inicializador);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Desativar Projetil", Keywords = "Desativar Projetil"), Category = "Projetil")
		void DesativarProjetil();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos", Keywords = "Spawn Efeitos"), Category = "Projetil")
		void SpawnEfeitos(const FHitResult& Hit);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Particula")
		void Atingiu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Hit", Keywords = "On Hit"), Category = "Particula")
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
		virtual void OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);




};
