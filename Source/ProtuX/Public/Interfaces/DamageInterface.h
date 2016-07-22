// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageInterface.generated.h"

/*
*	Classe derivada da classe UInterface
*	Interface responsável pela implementação do dano a objetos que podem receber dano. (Player e inimigos).
*	A diferença entre UDanoInterface e IDanoInterface é apenas para tanto o código quanto blueprints poderem acessar a interface.
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
	*	Função virtual para receber dano.
	*	@param dano - O dano a ser relizado.
	*	@param projetil - O projétil responsável pelo dano causado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Receber Dano", Keywords = "Receber Dano"), Category = "DanoInterface")
	virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit);

	/*
	*	Função virtual para aplicar os stats ao projétil
	*	@param projetil - O projétil que aplicara o seus stats ao objeto que chama esta função
	*/
	virtual void ApplyProjectileStats(AProjectile* projectile);

#pragma endregion
};
