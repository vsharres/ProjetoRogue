// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProtuXPlayer.h"
#include "PickUp.generated.h"

/* Enumera��o que representa o tipo de pickup. O tipo � o stats que ser� modificado quando o jogador obt�m o pickup. */
UENUM(BlueprintType)
enum class EPickUpType : uint8 {
	SCRAP,
	ENERGY,
	HEALTH,
	ITEM
};

/*
* Classe abstrata que representa um objeto que os inimigos criam quando s�o destru�dos.
*/
UCLASS(abstract)
class PROTUX_API APickUp : public AActor
{
	GENERATED_BODY()
#pragma region Properties
	
protected:

	/* Componente de colis�o. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		USphereComponent* TriggerCatch;

	/* Trigger para ativar o efeito de outline.*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
		USphereComponent* TriggerOutline;

	/* Mesh do pickup. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UStaticMeshComponent* Mesh;

public:

	/* Delta do vetor de posi��o do centro da for�a de explos�o. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosionDelta;

	/* Magnitude da for�a da explos�o. */
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

/* Constructor Padr�o. */
	APickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

	/*
	* Fun��o Get para retornar o componente de colis�o do Pickup.
	* @return Ponteiro ao componente de colis�o.
	*/
	UFUNCTION(BlueprintPure, Category = "Colisor")
		USphereComponent* GetCollider();

	/*
	* Fun��o Get para retornar o Mesh do Pickup.
	* @return Ponteiro ao Mesh.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		UStaticMeshComponent* GetMesh();

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion Functions

	
	
};
