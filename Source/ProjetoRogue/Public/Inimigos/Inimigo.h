// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Inimigo.generated.h"

UENUM(BlueprintType)
enum class ETipoInimigo :uint8
{
	BOT,
	TORRE,
	BOSS
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
		int32 Energia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo Struct")
		ETipoInimigo Tipo;

	FInimigoStats(float vida = 100.0f, float dano = 1.0f, int32 energia = 1, ETipoInimigo tipo = ETipoInimigo::BOT)
	{
		Vida = vida;
		VidaAtual = Vida;
		Dano = dano;
		Energia = energia;
		Tipo = tipo;
	}

};

UCLASS()
class PROJETOROGUE_API AInimigo : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inimigo")
		FInimigoStats Stats;

	// Sets default values for this pawn's properties
	AInimigo();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



};
