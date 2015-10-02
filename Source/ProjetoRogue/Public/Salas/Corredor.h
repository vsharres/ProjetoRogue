// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Corredor.generated.h"

/*
*/
UCLASS()
class PROJETOROGUE_API ACorredor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
		float OffsetCorredor;

	UPROPERTY(EditDefaultsOnly)
		FVector EscalaPadrao;

public:	
	// Sets default values for this actor's properties
	ACorredor(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		FVector GetEscala();

	UFUNCTION()
		int32 GetOffset();

	
	
};
