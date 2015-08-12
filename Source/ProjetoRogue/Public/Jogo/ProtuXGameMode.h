// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ProtuXGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AProtuXGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNovoJogo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 NumJogos;

	AProtuXGameMode(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadProfile();
	
	
};
