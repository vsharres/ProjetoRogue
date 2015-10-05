// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inimigos/Inimigo.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API ABoss : public AInimigo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
		bool bBossDerrotado;

	ABoss(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	
};
