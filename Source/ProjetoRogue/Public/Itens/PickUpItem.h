// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#pragma once

#include "Itens/PickUp.h"
#include "PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOROGUE_API APickUpItem : public APickUp
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = Item)
		TArray<TSubclassOf<class UItem>> PossiveisItems;

public:

	UPROPERTY(EditAnywhere, Category = Item)
		TSubclassOf<UItem> ItemAgerar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Item)
	class UItem* ItemGerado;

	APickUpItem(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Item)
		void EscolherItem(FRandomStream& Stream);

	/*
	* Função delegate a ser executada quando o colisor do pickup inicia um overlap com o jogador.
	* Assinatura da função determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	/*
	* Função delegate a ser executada quando o trigger de outline inicia um overlap do jogador.
	* Assinatura da função determinada pelo Delegate OnBeignOverlap.
	*/
	UFUNCTION()
		void OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Função delegate a ser executada quando o trigger de outline termina um overlap do jogador.
	* Assinatura da função determinada pelo Delegate OnEndOverlap.
	*/
	UFUNCTION()
		void OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
