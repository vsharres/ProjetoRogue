// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inimigo.h"
#include "InimigoRange.generated.h"

/*
* Classe derivada da classe AInimigo.
* Classe do inimigo que pode atirar proj�teis. 
*/
UCLASS()
class PROJETOROGUE_API AInimigoRange : public AInimigo
{
	GENERATED_BODY()

#pragma region Propriedades
public:
		/* Classe do proj�til a ser disparado. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

		/* Array de projeteis a serem disparados.s */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			TArray<AProjectil*> ProjetilPool;
		/* N�mero de proj�teis. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			int32 NumProjeteis;
		/* Booleando que indica quando o inimigo est� atirando. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
			bool bEstaAtirando;
#pragma endregion Propriedades

#pragma region Construtor
		/* Construtor padr�o. */
		AInimigoRange(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Fun��es
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Destroyed() override;

		virtual void CalcularStats(int32 levelAtual) override;

		/* Fun��o para gerar o pool de proj�teis a serem disparados. */
		UFUNCTION()
			void GerarProjetilPool();

		/* Fun��o para atirar um proj�til. */
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Inimgo")
			void Atirar();
		virtual void Atirar_Implementation();
#pragma endregion Fun��es

		
	
	
};
