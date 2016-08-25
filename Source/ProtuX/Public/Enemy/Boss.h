// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "Boss.generated.h"

/***
 * Class inherited from AEnemy
 * Class responsible for the Boss for every level in the game.
 */
UCLASS()
class PROTUX_API ABoss : public AEnemy
{
	GENERATED_BODY()
public:

	/** Boss armor, which is always equals or lower to 1.0 */
	UPROPERTY(EditDefaultsOnly, Category = Boss)
		float Armor;

	/** Collision component for the boss weak point */
	UPROPERTY(VisibleDefaultsOnly, Category = Colisor)
		USphereComponent* WeakPoint;

	/** boolean of true if the boss was defeated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
		bool bIsBossDefeated;

	/** Default constructor */
	ABoss(const FObjectInitializer& ObjectInitializer);

	/**
	 Interface function to receive damage.
	 @param damage - float damage value.
	 @param projectile - pointer to the projectile that caused damage.
	 @param Hit - Hit struct.
	*/
	virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	/**
	  Override of the calculate stats function.
	*/
	virtual void CalculateStats(int32 currentLevel) override;

	/**
		Event triggered when the boss is defeated.
	*/
	UFUNCTION(BlueprintCallable, Category = Boss)
		void OnBossDefeated();
	
};
