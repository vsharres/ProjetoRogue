// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BillboardComponent.h"
#include "Sala.h"
#include "InimigoSpawnerComponent.generated.h"

/*
 * Classe derivada da UBillboardComponent
 * Componente da sala responsável por fazer o spawn dos inimigos.
 */
UCLASS(ClassGroup = InimigoSpawner, meta = (BlueprintSpawnableComponent))
class PROJETOROGUE_API UInimigoSpawnerComponent : public UBillboardComponent
{
	GENERATED_BODY()

#pragma region Propriedades

public:

	/* Booleano para gerar o inimigo randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		bool bGerarRandomicamente;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TArray<TSubclassOf<class AInimigo>> InimigosRandomicosNormal;

	/* Array com as classes dos inimigos que podem ser gerados randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TArray<TSubclassOf<class AInimigo>> InimigosRandomicosDificil;

	/* Classe do inimigo a ser gerado não randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TSubclassOf<AInimigo> InimigoNaoRandomicoNormal;

	/* Classe do inimigo a ser gerado não randomicamente. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InimigoSpawner)
		TSubclassOf<AInimigo> InimigoNaoRandomicoDificil;

#pragma endregion Propriedades
	
#pragma region Construtor

	/* Construtor padrão. */
	UInimigoSpawnerComponent();

#pragma endregion Construtor

#pragma region Funções

	UFUNCTION()
		int32 GetNumInimigos(EDificuldadeSala Dificuldade);

	/*
	* Função para selecionar o inimigo que vai ser gerado randomicamente a partir do array de inimigos.
	* @param Stream - Stream randomico de geração.
	*/
	UFUNCTION(BlueprintCallable, Category = InimigoSpawner)
	TSubclassOf<AInimigo> SelecionarInimigoRandomicamente(FRandomStream& Stream, EDificuldadeSala Dificuldade);

#pragma endregion Funções

};
