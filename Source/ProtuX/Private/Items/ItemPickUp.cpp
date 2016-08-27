// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#include "ProtuX.h"
#include "ItemPickUp.h"

AItemPickUp::AItemPickUp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing properties
	Type = EPickUpType::ITEM;

	//Assigning trigger delegates
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &AItemPickUp::ColliderOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &AItemPickUp::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &AItemPickUp::OutlineEndOverlap);
}

void AItemPickUp::ChooseItem(FRandomStream& Stream)
{
	if (PossibleItems.Num() > 0)
	{
		//randomly pick an item to spawn
		ItemToSpawn = PossibleItems[Stream.FRandRange(0, PossibleItems.Num() - 1)];
	}
}

void AItemPickUp::ColliderOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{	
		//spawn new item
		SpawnedItem = NewObject<UItem>(this, ItemToSpawn);

		if (SpawnedItem)
		{
			//Initialize item and generate item pop up and destroy the pop up
			SpawnedItem->InitializeItem(player);
			player->GenerateItemPopUp(this);
			Destroy();
		}
		
	}
}

void AItemPickUp::OutlineOnOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(true); //activate outline effect
	}
}

void AItemPickUp::OutlineEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtuXPlayer* player = Cast<AProtuXPlayer>(OtherActor);

	if (player->IsValidLowLevelFast() && OtherComp) //check if the overlap was caused by the player
	{
		Mesh->SetRenderCustomDepth(false); //deactivate outline effect
	}
}
