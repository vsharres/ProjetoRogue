// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectil.generated.h"

UCLASS()
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	float Velocidade;

	UPROPERTY()
	int32 Dano;
	
public:	
	// Sets default values for this actor's properties
	AProjectil();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
