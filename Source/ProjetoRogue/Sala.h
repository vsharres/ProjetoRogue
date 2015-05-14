// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.generated.h"

UENUM(BlueprintType)
enum class ENumeroPortas : uint8
{
	ZERO,
	UMA,
	DUAS,
	TRES,
	QUATRO,

};

UENUM(BlueprintType)
enum class EDirecaoPortas : uint8
{
	LESTE,
	NORTE,
	OESTE,
	SUL,

};

UCLASS()
class PROJETOROGUE_API ASala : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		ENumeroPortas Numero_Portas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ASala*> Salas_Conectadas;

	UPROPERTY(BlueprintReadWrite)
		bool bVisited;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <EDirecaoPortas> Direcao_Portas;


public:

	// Sets default values for this actor's properties
	ASala();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
