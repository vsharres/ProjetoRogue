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

	FProjetilStats(float velocidade = 200.0f, float dano = 1.0f, float tamanho = 1.0f)
	{
		Velocidade = velocidade;
		Dano = dano;
		Tamanho = tamanho;
	}

	FORCEINLINE FProjetilStats& operator+=(const FJogadorStats& statsJogador)
	{
		this->Velocidade += statsJogador.VelocidadeMov;
		this->Dano += statsJogador.Dano;
		this->Tamanho += statsJogador.TamanhoProjetil;

		return *this;
	}


};

//TODO
UCLASS()
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FProjetilStats Stats;

	// Sets default values for this actor's properties
	AProjectil();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;



};
