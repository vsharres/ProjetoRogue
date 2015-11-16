// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ProtuXGameMode.generated.h"

UENUM()
enum class EJogoEstado : uint8{
	MENUPRINCIPAL,
	NOVOJOGO,
	CONTINUARJOGO,
	PROXIMAFASE,
	REINICIAR,
	GAMEOVER
};

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API AProtuXGameMode : public AGameMode
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		EJogoEstado Estado;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNaoSalvar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bNovoJogo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 NumJogos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		int32 LevelAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		bool bTutorialAtivado;

	AProtuXGameMode(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		EJogoEstado GetEstadoJogo() const;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void SetEstadoJogo(EJogoEstado NovoEstado);

	UFUNCTION()
		void AtualizarEstado(EJogoEstado NovoEstado);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadNovoJogo();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadContinuarJogo();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LoadProximaFase();
	
};
