// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#pragma once

#include "Items/PickUp.h"
#include "ItemPickUp.generated.h"

/**
 * 
 */
UCLASS()
class PROTUX_API AItemPickUp : public APickUp
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = Item)
		TArray<TSubclassOf<class UItem>> PossibleItems;

public:

	UPROPERTY(EditAnywhere, Category = Item)
		TSubclassOf<UItem> ItemToSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Item)
	class UItem* ItemGerado;

	AItemPickUp(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Item)
		void ChoseItem(FRandomStream& Stream);

	/*
	* Função delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da função determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	/*
	* Função delegate a ser executada quando o trigger de outline inicia um overlap do jogador.
	* Assinatura da função determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Função delegate a ser executada quando o trigger de outline termina um overlap do jogador.
	* Assinatura da função determinada pelo Delegate OnEndOverlap.
	*/
	UFUNCTION()
		void OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
