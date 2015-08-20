// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS(abstract)
class PROJETOROGUE_API APickUp : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UCapsuleComponent* Colisor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UStaticMeshComponent* Mesh;
	

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		float IncVida;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncEnergia;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncMoedas;

	// Sets default values for this actor's properties
	APickUp(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Colisor")
		UCapsuleComponent* GetColisor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
