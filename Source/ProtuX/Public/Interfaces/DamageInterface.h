// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageInterface.generated.h"

/**
*	Class inherited from UInterface
*	Interface responsible for the implementation of the damage to the player and enemies.
*	The diference between UdamageInterface and IDamageInterface is only so that blueprints can access the interface.
*/
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UDamageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IDamageInterface
{
	GENERATED_IINTERFACE_BODY()

#pragma region Functions

	/**
	*	Virtual function to receive damage.
	*	@param damage - Damage dealt
	*	@param projectile - Projectile that caused the damage
	*	@param Hit - Hit results of the point of impact 
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Receive Damage", Keywords = "Receive Damage"), Category = "Interface")
	virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit);

	/**
	*	Virtual function to apply the stats to the projectile
	*	@param projectile - Projectile that will apply the stats to the caller of this function.
	*/
	virtual void ApplyProjectileStats(AProjectile* projectile);

#pragma endregion
};
