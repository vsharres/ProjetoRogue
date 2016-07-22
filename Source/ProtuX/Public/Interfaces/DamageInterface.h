// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageInterface.generated.h"

/*
*	Classe derivada da classe UInterface
*	Interface respons�vel pela implementa��o do dano a objetos que podem receber dano. (Player e inimigos).
*	A diferen�a entre UDanoInterface e IDanoInterface � apenas para tanto o c�digo quanto blueprints poderem acessar a interface.
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

	/*
	*	Fun��o virtual para receber dano.
	*	@param dano - O dano a ser relizado.
	*	@param projetil - O proj�til respons�vel pelo dano causado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Receber Dano", Keywords = "Receber Dano"), Category = "DanoInterface")
	virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit);

	/*
	*	Fun��o virtual para aplicar os stats ao proj�til
	*	@param projetil - O proj�til que aplicara o seus stats ao objeto que chama esta fun��o
	*/
	virtual void ApplyProjectileStats(AProjectile* projectile);

#pragma endregion
};
