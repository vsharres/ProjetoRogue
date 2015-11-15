// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#include "ProjetoRogue.h"
#include "PickUpItem.h"
#include "Jogador.h"

APickUpItem::APickUpItem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Tipo = ETipoPickUp::ITEM;
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpItem::OutlineEndOverlap);
}

void APickUpItem::EscolherItem(FRandomStream& Stream)
{
	ItemAgerar = PossiveisItems[Stream.FRandRange(0, PossiveisItems.Num() - 1)];
}

void APickUpItem::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{			
		ItemGerado = NewObject<UItem>(this, ItemAgerar);

		if (ItemGerado)
		{
			ItemGerado->InicializarItem(jogador);
			jogador->GerarItemPopUp(this);
			Destroy();
		}
		
	}
}

void APickUpItem::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void APickUpItem::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void APickUpItem::BeginPlay()
{
	TriggerCatch->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Super::BeginPlay();
}
