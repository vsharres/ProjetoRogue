// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "PickUp.generated.h"

/* Enumeração que representa o tipo de pickup. O tipo é o stats que será modificado quando o jogador obtêm o pickup. */
UENUM(BlueprintType)
enum class EPickUpType : uint8 {
	SCRAP,
	ENERGY,
	HEALTH,
	ITEM
};

/*
* Classe abstrata que representa um objeto que os inimigos criam quando são destruídos.
*/
UCLASS(abstract)
class PROTUX_API APickUp : public AActor
{
	GENERATED_BODY()
#pragma region Properties
	
protected:

	/* Componente de colisão. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		USphereComponent* TriggerCatch;

	/* Trigger para ativar o efeito de outline.*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
		USphereComponent* TriggerOutline;

	/* Mesh do pickup. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UStaticMeshComponent* Mesh;

public:

	/* Delta do vetor de posição do centro da força de explosão. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosionDelta;

	/* Magnitude da força da explosão. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosionForce;

	/* Quanto o item potencialmente incrementa a vida do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		float IncHealth;

	/* Quanto o item potencialmente incrementa a energia do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncEnergy;

	/* Quanto o item potencialmente incrementa a quantidade de moedas do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncScraps;

	/* O tipo do pickup. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
		EPickUpType	Type;

#pragma endregion Properties

#pragma region Constructor

/* Constructor Padrão. */
	APickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

	/*
	* Função Get para retornar o componente de colisão do Pickup.
	* @return Ponteiro ao componente de colisão.
	*/
	UFUNCTION(BlueprintPure, Category = "Colisor")
		USphereComponent* GetCollider();

	/*
	* Função Get para retornar o Mesh do Pickup.
	* @return Ponteiro ao Mesh.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		UStaticMeshComponent* GetMesh();

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion Functions

	
	
};
