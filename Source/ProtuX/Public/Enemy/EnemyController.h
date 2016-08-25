// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyController.generated.h"

/***
 * Class inherited from AAIController.
 * Enemy controller, class responsible for enemy's AI.
 */
UCLASS()
class PROTUX_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
#pragma region Properties
public:
	/** Weak pointer to the room in which the enemy is located. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room")
	TWeakObjectPtr<class ARoom> ParentRoom;
#pragma endregion Properties

#pragma region Construtor
	/** Default Constructor. */
	AEnemyController();
#pragma endregion Construtor

#pragma region Functions

	/** Event triggered to deactivate the enemy. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Deactivate Enemy", Keywords = "Deactivate Enemy"), Category = "Enemy Controller")
		void DeactivateEnemy();

	/** Event triggered to activate the enemy.  */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Activate Enemy", Keywords = "Activate Enemy"), Category = "Enemy Controller")
		void ActivateEnemy();
#pragma endregion Functions
	
};
