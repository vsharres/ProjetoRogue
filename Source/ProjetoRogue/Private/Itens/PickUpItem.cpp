// ProtuX made by Vinicius Harres, Caio Conto and Tiago Higa

#include "ProjetoRogue.h"
#include "PickUpItem.h"
#include "Jogador.h"

APickUpItem::APickUpItem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	Tipo = ETipoPickUp::ITEM;

	//Criando os delegates de overlap
	TriggerCatch->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::ColisorOverlap);
	TriggerOutline->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OutlineOnOverlap);
	TriggerOutline->OnComponentEndOverlap.AddDynamic(this, &APickUpItem::OutlineEndOverlap);
}

void APickUpItem::EscolherItem(FRandomStream& Stream)
{
	//Escolher randomicamente o item a ser gerado.
	ItemAgerar = PossiveisItems[Stream.FRandRange(0, PossiveisItems.Num() - 1)]; 
}

void APickUpItem::ColisorOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{	
		//Spawn do novo item.
		ItemGerado = NewObject<UItem>(this, ItemAgerar);

		if (ItemGerado)
		{
			//Inicializar o item e gerar o popup
			ItemGerado->InicializarItem(jogador);
			jogador->GerarItemPopUp(this);
			Destroy();
		}
		
	}
}

void APickUpItem::OutlineOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(true); //Ativar o outline do pickup
	}
}

void APickUpItem::OutlineEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && OtherComp) //checar que o overlap foi causado pelo jogador.
	{
		Mesh->SetRenderCustomDepth(false); //desativar o outline do pickup
	}
}
