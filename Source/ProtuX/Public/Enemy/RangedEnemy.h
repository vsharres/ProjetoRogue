// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "RangedEnemy.generated.h"

/*
* Classe derivada da classe AInimigo.
* Classe do inimigo que pode atirar proj�teis. 
*/
UCLASS()
class PROTUX_API ARangedEnemy : public AEnemy
{
	GENERATED_BODY()

#pragma region Propriedades
public:
		/* Classe do proj�til a ser disparado. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
		TSubclassOf<class AProjectile> Projectile;

		/* Array de projeteis a serem disparados.s */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			TArray<AProjectile*> ProjectilePool;
		/* N�mero de proj�teis. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil")
			int32 NumProjectiles;
		/* Booleando que indica quando o inimigo est� atirando. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inimigo)
			bool bIsFiring;
#pragma endregion Propriedades

#pragma region Construtor
		/* Construtor padr�o. */
		ARangedEnemy(const FObjectInitializer& ObjectInitializer);
#pragma endregion Construtor

#pragma region Fun��es
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Destroyed() override;

		virtual void CalculateStats(int32 currentLevel) override;

		/* Fun��o para gerar o pool de proj�teis a serem disparados. */
		UFUNCTION()
			void GenerateProjectilesPool();

		/* Fun��o para atirar um proj�til. */
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Inimgo")
			void Attack();
		virtual void Attack_Implementation();
#pragma endregion Fun��es

		
	
	
};
