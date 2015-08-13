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

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		int32 NumeroSalas;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Salas")
		int32 IndexSala2P;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Salas")
		int32 IndexSala3P;

	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "3"), Category = "Salas")
		int32 IndexSala4P;

	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ASala> SalaItem;

	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ASala> SalaChave;

	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ASala> SalaBoss;

	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<class ACorredor> Corredor;

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaItemGerada;

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaChaveGerada;

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaBossGerada;

	UPROPERTY(VisibleAnywhere, Category = "Salas")
		TSubclassOf<ASala> SalaGerada;

	UPROPERTY()
		TArray<TSubclassOf<ASala>> UltimasSalasGeradas;

	UPROPERTY()
		TArray<FVector> PosSalas;

	UPROPERTY()
		TArray<bool> SalasCarregadas;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<TSubclassOf<ASala>> TiposSalas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "30"))
		int32 MaxNumSalas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "30"))
		int32 MinNumSalas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		ASala* SalaInicial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<ASala*> Salas;

public:
	// Sets default values for this actor's properties
	ASalasGerador();

	~ASalasGerador();

	UFUNCTION(BlueprintPure, Category = "Gerador Salas", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ASalasGerador* GetGeradorSalas(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void Inicializar(ASala* Inicial);

	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		FRotator GetDirecaoPorta(const FRotator DirecaoSala, const EDirecaoPorta& Porta);

	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 GetNumPortasVazias();

	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 UltimaSalaValida();

	UFUNCTION()
		FTransform GerarTransformSala(const ASala* SalaAnterior, const FRotator DirecaoPorta);

	UFUNCTION()
		FTransform GerarTransformCorredor(const ASala* SalaAnterior, const FRotator DirecaoPorta);

	UFUNCTION()
		TSubclassOf<ASala> SelecionarSala(const ASala* SalaAnterior);

	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SetNumSalas();

	UFUNCTION()
		void AdicionarAoArrayPortas(ASala* sala);

	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void GerarLevel(ASala* SalaAtual);

	UFUNCTION()
		ASala* GerarSala(ASala* SalaAnterior, const FRotator DirecaoPorta);

	UFUNCTION()
		void ImpedirColisao(const FTransform& Trans, const FRotator DirecaoPorta);

	UFUNCTION()
		void GerarSalaEspecial();

	UFUNCTION()
		bool EstaNoArrayDePosicoes(const FVector& pos);

	UFUNCTION()
		bool ColideNaDirecao(EDirecaoPorta Direcao, const FTransform& Trans);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sala")
		virtual void GeracaoTerminada();

	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void CarregarSalas();

	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SalvarSalas();


};
