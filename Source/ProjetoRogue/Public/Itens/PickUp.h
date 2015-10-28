// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

/* Enumeração que representa o tipo de pickup. O tipo é o stats que será modificado quando o jogador obtêm o pickup. */
UENUM(BlueprintType)
enum class ETipoPickUp : uint8 {
	MOEDA,
	ENERGIA,
	VIDA
};

/*
* Classe abstrata que representa um objeto que os inimigos criam quando são destruídos.
*/
UCLASS(abstract)
class PROJETOROGUE_API APickUp : public AActor
{
	GENERATED_BODY()
#pragma region PROPRIEDADES
	
protected:

	/* Componente de colisão. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		USphereComponent* TriggerCatch;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
		USphereComponent* TriggerOutline;

	/* Mesh do pickup. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
		UStaticMeshComponent* Mesh;

public:

	/* Delta do vetor de posição do centro da força de explosão. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
		float ExplosaoDelta;

	/* Magnitude da força da explosão. */
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

/* Construtor Padrão. */
	APickUp(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUNÇÕES

	/*
	* Função Get para retornar o componente de colisão do Pickup.
	* @return Ponteiro ao componente de colisão.
	*/
	UFUNCTION(BlueprintPure, Category = "Colisor")
		USphereComponent* GetColisor();

	/*
	* Função Get para retornar o Mesh do Pickup.
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

#pragma endregion FUNÇÕES

	
	
};
