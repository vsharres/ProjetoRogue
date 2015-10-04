// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BillboardComponent.h"
#include "InimigoSpawnerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = InimigoSpawner, meta = (BlueprintSpawnableComponent))
class PROJETOROGUE_API UInimigoSpawnerComponent : public UBillboardComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		bool bGerarRandomicamente;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TSubclassOf<class AInimigo> InimigoNaoRandomico;
	
	UInimigoSpawnerComponent();
};
