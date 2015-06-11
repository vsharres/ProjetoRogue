// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Public/Jogador/Jogador.h"
#include "Projectil.generated.h"

USTRUCT()
struct FProjetilStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Dano;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Tamanho;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float ProjetilVida;

	FProjetilStats(float velocidade = 200.0f, float dano = 1.0f, float tamanho = 1.0f, float projetilvida = 10.0f)
	{
		Velocidade = velocidade;
		Dano = dano;
		Tamanho = tamanho;
		ProjetilVida = projetilvida;
	}

	FORCEINLINE FProjetilStats& operator+=(const FJogadorStats& statsJogador)
	{
		this->Velocidade += statsJogador.VelocidadeMov;
		this->Dano += statsJogador.Dano;
		this->Tamanho += statsJogador.TamanhoProjetil;
		this->ProjetilVida += statsJogador.Range;

		return *this;
	}


};

//TODO
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
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



};
