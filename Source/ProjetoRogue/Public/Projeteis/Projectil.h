// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Public/Jogador/Jogador.h"
#include "Public/Inimigos/Inimigo.h"
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
		float Tamanho;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Range;

	FProjetilStats(float velocidade = 200.0f, float dano = 1.0f, float tamanho = 1.0f, float range = 10.0f)
	{
		Velocidade = velocidade;
		Dano = dano;
		Tamanho = tamanho;
		Range = range;
	}

	FORCEINLINE FProjetilStats& operator=(const FJogadorStats& statsJogador)
	{
		this->Velocidade = statsJogador.VelProjetil;
		this->Dano = statsJogador.Dano;
		this->Tamanho = statsJogador.TamanhoProjetil;
		this->Range = statsJogador.Range;

		return *this;
	}

	FORCEINLINE FProjetilStats& operator=(const FInimigoStats& statsInimigo)
	{
		this->Velocidade = statsInimigo.VelProjetil;
		this->Dano = statsInimigo.Dano;
		this->Tamanho = statsInimigo.TamanhoProjetil;
		this->Range = statsInimigo.Range;

		return *this;
	}


};

//TODO
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FProjetilStats Stats;

	UPROPERTY(VisibleDefaultsOnly, Category = Projetil)
		UProjectileMovementComponent* CompMovimentacao;

	UPROPERTY(VisibleDefaultsOnly, Category = Projetil)
		USphereComponent* CompCollisao;

	UPROPERTY(VisibleDefaultsOnly, Category = Projetil)
		UStaticMeshComponent* Mesh;

	// Sets default values for this actor's properties
	AProjectil(const FObjectInitializer& ObjectInitializer);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Hit", Keywords = "On Hit"), Category = "Particula")
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
		virtual void OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Proj", Keywords = "Get Mov Proj"), Category = "Particula")
			UProjectileMovementComponent* GetMovProjetil();



};
