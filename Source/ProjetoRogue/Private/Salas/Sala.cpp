// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala.h"
#include "Inimigo.h"
#include "InimigosControlador.h"
#include "Porta.h"
#include "Jogador.h"
#include "SalasGerador.h"
#include "InimigoSpawnerComponent.h"


// Sets default values
ASala::ASala(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerAtivarInimigos = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerAtivarInimigos"));
	TriggerAtivarInimigos->SetBoxExtent(FVector(300.0f, 300.0f, 32.0f));
	TriggerAtivarInimigos->OnComponentBeginOverlap.AddDynamic(this, &ASala::AtivarInimigosTriggerOnOverlap);
	TriggerAtivarInimigos->OnComponentEndOverlap.AddDynamic(this, &ASala::AtivarInimigosTriggerEndOverlap);
	RootComponent = TriggerAtivarInimigos;

	bCanBeDamaged = false;
	NumeroPortas = ENumeroPortas::UMA;
	DirecaoSala = EFormatoSala::PADRAO;
	TipoSala = ETipoSala::NORMAL;
	Dificuldade = EDificuldadeSala::FACIL;
	SalasConectadas.Empty();
	DirecaoPortas.Add(EDirecaoPorta::OESTE);
	Portas.Empty();
	bVisitada = false;
	bSalaTemInimigos = false;
	Inimigos.Empty();
	OffsetSala = 6000.0f;
	EscalaPadrao = FVector(1.0f, 1.0f, 1.0f);


}



void ASala::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InimigosForamDerrotados();

}

void ASala::BeginPlay()
{
	Super::BeginPlay();

	if (!bSalaTemInimigos)
	{
		TriggerAtivarInimigos->OnComponentBeginOverlap.RemoveAll(this);
		TriggerAtivarInimigos->OnComponentEndOverlap.RemoveAll(this);
	}
}

FVector ASala::GetEscala()
{
	return EscalaPadrao;
}

float ASala::GetOffset() const
{
	return OffsetSala;
}

ENumeroPortas ASala::GetNumPortas()
{
	return NumeroPortas;
}

EFormatoSala ASala::GetDirecao()
{
	return DirecaoSala;
}

ETipoSala ASala::GetTipo()
{
	return TipoSala;
}

TArray<TEnumAsByte<EDirecaoPorta>> ASala::GetArrayPortas()
{
	return DirecaoPortas;
}

void ASala::SetOffset(float novoOffset)
{
	this->OffsetSala = novoOffset;
}

void ASala::RemoverInimigo(AInimigo* inimigo)
{
	if (inimigo)
	{
		Inimigos.Remove(inimigo);
	}
}

void ASala::SpawnInimigos_Implementation(FRandomStream& Stream)
{
	if (!bSalaTemInimigos)
		return;

	TInlineComponentArray<UInimigoSpawnerComponent*> Componentes;
	this->GetComponents(Componentes);

	TArray<TSubclassOf<AInimigo>> TipoInimigo;

	switch (Dificuldade)
	{
	case EDificuldadeSala::FACIL:
		TipoInimigo = InimigosFacil;
		break;
	case EDificuldadeSala::NORMAL:
		TipoInimigo = InimigosNormal;
		break;
	case EDificuldadeSala::DIFICIL:
		TipoInimigo = InimigosDificil;
		break;
	default:
		checkNoEntry();
		break;
	}

	for (const auto& Spawner : Componentes)
	{
		FTransform SpawnTrans = FTransform(FRotator::ZeroRotator, Spawner->GetComponentLocation());

		AInimigo* NovoInimigo;

		if (Spawner->bGerarRandomicamente)
		{
			check(TipoInimigo.Num() > 0);
			if (Spawner->InimigosRandomicos.Num() > 0)
			{
				NovoInimigo = GetWorld()->SpawnActor<AInimigo>(Spawner->SelecionarInimigoRandomicamente(Stream), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
			else
			{
				NovoInimigo = GetWorld()->SpawnActor<AInimigo>(GetTipoInimigo(TipoInimigo,Stream), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}
		else
		{
			TSubclassOf<AInimigo> InimigoNaoRandomico;
			InimigoNaoRandomico = Spawner->InimigoNaoRandomico;

			NovoInimigo = GetWorld()->SpawnActor<AInimigo>(InimigoNaoRandomico, Spawner->GetComponentLocation(), FRotator::ZeroRotator);
		}

		if (NovoInimigo->IsValidLowLevelFast())
		{
			NovoInimigo->SpawnDefaultController();
			Inimigos.Add(NovoInimigo);
			NovoInimigo->SalaPai = this;
		}

		AInimigosControlador* Controlador = Cast<AInimigosControlador>(NovoInimigo->GetController());

		if (Controlador->IsValidLowLevelFast())
		{
			Controlador->SalaPai = this;
		}
	}
}

TSubclassOf<AInimigo> ASala::GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade,FRandomStream& Stream)
{
	TSubclassOf<AInimigo> tipoInimigo = InimigoDificuldade[Stream.FRandRange(0, InimigoDificuldade.Num() - 1)];

	return tipoInimigo;

}

void ASala::InimigosForamDerrotados()
{
	if (Inimigos.Num() == 0 && bSalaTemInimigos)
	{
		for (const auto& Porta : Portas)
		{
			Porta->DestrancarPorta();
		}

		bSalaTemInimigos = false;
		bInimigosAtivos = false;
		TriggerAtivarInimigos->OnComponentBeginOverlap.RemoveAll(this);
		TriggerAtivarInimigos->OnComponentEndOverlap.RemoveAll(this);
		DestrancarPortas();

		AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());
		ASalasGerador* gerador = ASalasGerador::GetGeradorSalas(GetWorld());

		if (jogador->IsValidLowLevelFast() && gerador->IsValidLowLevelFast())
		{
			jogador->SalvarJogador();
			gerador->SalvarSalas();
		}

		if (TipoSala == ETipoSala::BOSS)
		{

		}
	}

}

void ASala::TrancarPortas()
{
	for (const auto& Porta : Portas)
	{
		Porta->TrancarPorta();
	}

}

void ASala::AtivarInimigosTriggerOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AJogador>(OtherActor) && !bInimigosAtivos && bSalaTemInimigos)
	{
		for (auto const& Inimigo : Inimigos)
		{
			AInimigosControlador* controlador = Cast<AInimigosControlador>(Inimigo->GetController());

			if (controlador->IsValidLowLevelFast())
			{
				controlador->AtivarInimigo();
			}
		}

		TrancarPortas();
	}
}

void ASala::AtivarInimigosTriggerEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AJogador>(OtherActor) && bInimigosAtivos && bSalaTemInimigos)
	{
		for (auto const& Inimigo : Inimigos)
		{
			AInimigosControlador* controlador = Cast<AInimigosControlador>(Inimigo->GetController());

			if (controlador->IsValidLowLevelFast())
			{
				controlador->DesativarInimigo();
			}
		}
	}
}

void ASala::AlterarCorSala(FLinearColor novaCor, USceneComponent* Sala)
{
	TArray<USceneComponent*> meshs;

	Sala->GetChildrenComponents(true, meshs);

	for (auto const& componente : meshs)
	{
		UInstancedStaticMeshComponent* instMesh = Cast<UInstancedStaticMeshComponent>(componente);

		if (instMesh)
		{
			UMaterialInstanceDynamic* MID =  instMesh->CreateDynamicMaterialInstance(1);

			if (MID)
			{
				MID->SetVectorParameterValue("Base_Color", novaCor);
			}
		}
	}
}

