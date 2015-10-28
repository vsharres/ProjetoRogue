// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

/* Enumera��o que representa o tipo de pickup. O tipo � o stats que ser� modificado quando o jogador obt�m o pickup. */
UENUM(BlueprintType)
enum class ETipoPickUp : uint8 {
	MOEDA,
	ENERGIA,
	VIDA
};

/*
* Classe abstrata que representa um objeto que os inimigos criam quando s�o destru�dos.
*/
UCLASS(abstract)
class PROJETOROGUE_API APickUp : public AActor
{
	GENERATED_BODY()
#pragma region PROPRIEDADES
	
protected:

	/* Componente de colis�o. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		USphereComponent* TriggerCatch;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
		USphereComponent* TriggerOutline;

	/* Mesh do pickup. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UStaticMeshComponent* Mesh;

public:

	/* Delta do vetor de posi��o do centro da for�a de explos�o. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosaoDelta;

	/* Magnitude da for�a da explos�o. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosaoForca;

	/* Quanto o item potencialmente incrementa a vida do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		float IncVida;

	/* Quanto o item potencialmente incrementa a energia do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncEnergia;

	/* Quanto o item potencialmente incrementa a quantidade de moedas do jogador. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		int32 IncMoedas;

	/* O tipo do pickup. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
		ETipoPickUp Tipo;

#pragma endregion PROPRIEDADES

#pragma region CONSTRUTOR

/* Construtor Padr�o. */
	APickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUN��ES

	/*
	* Fun��o Get para retornar o componente de colis�o do Pickup.
	* @return Ponteiro ao componente de colis�o.
	*/
	UFUNCTION(BlueprintPure, Category = "Colisor")
		USphereComponent* GetColisor();

	/*
	* Fun��o Get para retornar o Mesh do Pickup.
	* @return Ponteiro ao Mesh.
	*/
	UFUNCTION(BlueprintPure, Category = "Mesh")
		UStaticMeshComponent* GetMesh();

	UFUNCTION()
		void OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Override do evento de beginplay. */
	virtual void BeginPlay() override;

#pragma endregion FUN��ES

	
	
};
