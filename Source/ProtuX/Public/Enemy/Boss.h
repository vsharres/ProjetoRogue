// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "Boss.generated.h"

/**
 * Classe Derivada do AInimigo
 * Classe respons�vel pelas propriedades de um Boss do jogo.
 */
UCLASS()
class PROTUX_API ABoss : public AEnemy
{
	GENERATED_BODY()
public:

	/* Armadura do boss, que � sempre um n�mero menor ou igual a 1.0 */
	UPROPERTY(EditDefaultsOnly, Category = Boss)
		float Armor;

	/* Componente de colis�o do ponto fraco */
	UPROPERTY(VisibleDefaultsOnly, Category = Colisor)
		USphereComponent* WeakPoint;

	/* Booleano indicando se o boss foi derrotado */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
		bool bIsBossDefeated;

	/* Construtor Padr�o */
	ABoss(const FObjectInitializer& ObjectInitializer);

	/*
	 Fun��o de interface para receber dano.
	 @param dano - float de dano.
	 @param prjetil - ponteiro do projetil que causou dano.
	 @param Hit - Resultados do hit do proj�til.
	*/
	virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	virtual void CalculateStats(int32 currentLevel) override;

	UFUNCTION(BlueprintCallable, Category = Boss)
		void OnBossDefeated();
	
};
