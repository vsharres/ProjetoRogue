// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inimigo.h"
#include "InimigoRange.generated.h"

/*
* Classe derivada da classe AInimigo.
* Classe do inimigo que pode atirar projéteis. 
*/
UCLASS()
class PROJETOROGUE_API AInimigoRange : public AInimigo
{
	GENERATED_BODY()

#pragma region Propriedades
public:
		/* Classe do projétil a ser disparado. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<class AProjectil> Projetil;

		/* Array de projeteis a serem disparados.s */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			TArray<AProjectil*> ProjetilPool;
		/* Número de projéteis. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			int32 NumProjeteis;
		/* Booleando que indica quando o inimigo está atirando. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
			bool bEstaAtirando;
#pragma endregion Propriedades

#pragma region Construtor
		/* Construtor padrão. */
		AInimigoRange(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Funções
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Destroyed() override;

		virtual void CalcularStats(int32 levelAtual) override;

		/* Função para gerar o pool de projéteis a serem disparados. */
		UFUNCTION()
			void GerarProjetilPool();

		/* Função para atirar um projétil. */
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Inimgo")
			void Atirar();
		virtual void Atirar_Implementation();
#pragma endregion Funções

		
	
	
};
