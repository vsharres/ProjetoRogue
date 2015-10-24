// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inimigo.h"
#include "InimigoRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AInimigoRange : public AInimigo
{
	GENERATED_BODY()

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			TArray<AProjectil*> ProjetilPool;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			int32 NumProjeteis;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
			bool bEstaAtirando;

		virtual void BeginPlay() override;

		virtual void Destroyed() override;

		UFUNCTION()
			void GerarProjetilPool();

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Inimgo")
			void Atirar();
		virtual void Atirar_Implementation();

		AInimigoRange(const FObjectInitializer& ObjectInitializer);
	
	
};
