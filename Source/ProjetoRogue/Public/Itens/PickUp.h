// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UENUM(BlueprintType)
enum class ETipoPickUp : uint8 {
	MOEDA,
	ENERGIA,
	VIDA
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosaoDelta;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosaoForca;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		float IncVida;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncEnergia;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncMoedas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
		ETipoPickUp Tipo;

	// Sets default values for this actor's properties
	APickUp(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Colisor")
		UCapsuleComponent* GetColisor();

	UFUNCTION(BlueprintPure, Category = "Mesh")
		UStaticMeshComponent* GetMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
