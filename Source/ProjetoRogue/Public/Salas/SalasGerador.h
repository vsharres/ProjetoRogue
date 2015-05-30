// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.h"
#include "SalasGerador.generated.h"

UCLASS()
class PROJETOROGUE_API ASalasGerador : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		int32 NumeroSalas;

	UPROPERTY(EditDefaultsOnly)
		int32 OffsetSala;

	UPROPERTY(EditDefaultsOnly)
		int32 OffsetCorredor;

	UPROPERTY(EditDefaultsOnly)
		FVector EscalaPadraoSalas;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<ASala>> TiposSalas;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASala> SalaItem;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASala> SalaChave;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASala> SalaBoss;

	UPROPERTY(VisibleAnywhere)
		bool bSalaItemGerada;

	UPROPERTY(VisibleAnywhere)
		bool bSalaChaveGerada;

	UPROPERTY(VisibleAnywhere)
		bool bSalaBossGerada;

public:
	UPROPERTY(EditAnywhere)
		int32 MaxNumSalas;

	UPROPERTY(EditAnywhere)
		int32 MinNumSalas;

	UPROPERTY(EditAnywhere)
		int32 Seed;

	UPROPERTY(EditAnywhere)
		ASala* SalaInicial;

	UPROPERTY(VisibleAnywhere)
		TArray<ASala*> Salas;

public:
	// Sets default values for this actor's properties
	ASalasGerador();

	UFUNCTION()
		FRotator GetDirecaoPorta(const FRotator& DirecaoSala, const EDirecaoPortas& Porta);

	UFUNCTION()
		int32 GetNumPortasVazias();

	UFUNCTION()
		int32 UltimaSalaValida();

	UFUNCTION()
		EDirecaoSala GetDirecaoSala(TSubclassOf<ASala> Classe);

	UFUNCTION()
		ENumeroPortas GetNumeroPortas(TSubclassOf<ASala> Classe);

	UFUNCTION()
		TArray< TEnumAsByte<EDirecaoPortas> > GerarArrayPortas(TSubclassOf<ASala> Classe);

	UFUNCTION()
		FTransform GerarTransformSala(const ASala* SalaAnterior, const FRotator& DirecaoPorta);

	UFUNCTION()
		FTransform GerarTransformCorredor(const ASala* SalaAnterior, const FRotator& DirecaoPorta);

	UFUNCTION()
		TSubclassOf<ASala> SelecionarSala();

	UFUNCTION()
		void SetNumSalas();

	UFUNCTION()
		void GerarLevel(ASala* SalaAtual);

	UFUNCTION()
		void GerarSala(ASala* SalaAnterior, const FRotator& DirecaoPorta);

	UFUNCTION()
		void ImpedirColisao(TSubclassOf<ASala> SalaGerada, const FTransform& Trans, const FRotator& DirecaoPorta);

	UFUNCTION()
		bool SalaEspecialGerada(TSubclassOf<ASala> SalaGerada);	

	UFUNCTION()
		bool ColideNaDirecao(EDirecaoPortas Direcao, const FTransform& Trans);

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
