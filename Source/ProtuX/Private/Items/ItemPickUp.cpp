// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#include "ProtuX.h"
#include "ItemPickUp.h"

AItemPickUp::AItemPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	Type = EPickUpType::ITEM;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AItemPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AItemPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AItemPickUp::OutlineEndOverlap);
}

void AItemPickUp::ChoseItem(FRandomStream& Stream)
{
	if (PossibleItems.Num() > 0)
	{
		//Escolher randomicamente o item a ser gerado.
		ItemToSpawn = PossibleItems[Stream.FRandRange(0, PossibleItems.Num() - 1)];
	}
}

void AItemPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{	
		//Spawn do novo item.
		ItemGerado = NewObject<UItem>(this, ItemToSpawn);

		if (ItemGerado)
		{
			//Inicializar o item e gerar o popup
			ItemGerado->InitializeItem(player);
			player->GenerateItemPopUp(this);
			Destroy();
		}
		
	}
}

void AItemPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void AItemPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}
