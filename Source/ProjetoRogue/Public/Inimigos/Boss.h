// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inimigos/Inimigo.h"
#include "Boss.generated.h"

/**
 * Classe Derivada do AInimigo
 * Classe responsável pelas propriedades de um Boss do jogo.
 */
UCLASS()
class PROJETOROGUE_API ABoss : public AInimigo
{
	GENERATED_BODY()
public:

	/* Armadura do boss, que é sempre um número menor ou igual a 1.0 */
	UPROPERTY(EditDefaultsOnly, Category = Boss)
		float Armadura;

	/* Componente de colisão do ponto fraco */
	UPROPERTY(VisibleDefaultsOnly, Category = Colisor)
		USphereComponent* PontoFraco;

	/* Booleano indicando se o boss foi derrotado */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
		bool bBossDerrotado;

	/* Construtor Padrão */
	ABoss(const FObjectInitializer& ObjectInitializer);

	/*
	 Função de interface para receber dano.
	 @param dano - float de dano.
	 @param prjetil - ponteiro do projetil que causou dano.
	 @param Hit - Resultados do hit do projétil.
	*/
	virtual void ReceberDano(const float& dano, AProjectil* projetil, const FHitResult& Hit) override;

	virtual void CalcularStats(int32 levelAtual) override;

	UFUNCTION(BlueprintCallable, Category = Boss)
		void BossDerrotado();
	
};
