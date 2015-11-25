// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala.h"
#include "Inimigo.h"
#include "InimigosControlador.h"
#include "Porta.h"
#include "Jogador.h"
#include "SalasGerador.h"
#include "InimigoSpawnerComponent.h"


// Construtor
ASala::ASala(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Inicializando o trigger de ativação dos inimigos
	TriggerAtivarInimigos = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerAtivarInimigos"));
	TriggerAtivarInimigos->SetBoxExtent(FVector(300.0f, 300.0f, 32.0f));
	
	//Trigger é o componente raiz do ator.
	RootComponent = TriggerAtivarInimigos;
	
	//Inicializando propriedades.
	bCanBeDamaged = false;
	NumeroPortas = ENumeroPortas::UMA;
	DirecaoSala = EFormatoSala::PADRAO;
	TipoSala = ETipoSala::NORMAL;
	Dificuldade = EDificuldadeSala::NORMAL;
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
	Super::Tick(DeltaTime); //Interface do Tick

	InimigosForamDerrotados(); //Checando se os inimigos foram derrotados

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

void ASala::DesativarTrigger()
{
	TriggerAtivarInimigos->OnComponentBeginOverlap.RemoveAll(this);
	TriggerAtivarInimigos->OnComponentEndOverlap.RemoveAll(this);
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
	if (!bSalaTemInimigos)//Se a sala não tem inimigos, nao fazer o spawn.
		return;

	TInlineComponentArray<UInimigoSpawnerComponent*> Componentes; 
	this->GetComponents(Componentes); //Encontrar todos os componentes de spawn no ator.

	TArray<TSubclassOf<AInimigo>> TipoInimigo; // Tipo do inimigo a ser feito spawn

	switch (Dificuldade) //Escolher o inimigos baseado na dificuldade da sala.
	{
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

	for (const auto& Spawner : Componentes) //Para cada ponto de spawn, escolher um inimigo e fazer o spawn
	{
		FTransform SpawnTrans = FTransform(FRotator::ZeroRotator, Spawner->GetComponentLocation()); //transform de spawn.

		AInimigo* NovoInimigo =  NULL;

		if (Spawner->bGerarRandomicamente) 
		{
			//check(TipoInimigo.Num() > 0);
			if (Spawner->GetNumInimigos(Dificuldade) > 0) //Garantir que nenhuma classe nula vai ser usada e que o ponto de spawn tem um tipo de inimigo especifico a ser usado.
			{
				//Spawn do inimigo randomicamente
				NovoInimigo = GetWorld()->SpawnActor<AInimigo>(Spawner->SelecionarInimigoRandomicamente(Stream,Dificuldade), Spawner->GetComponentLocation(), FRotator::ZeroRotator); 
			}
			else //usando os inimigos da sala.
			{
				NovoInimigo = GetWorld()->SpawnActor<AInimigo>(GetTipoInimigo(TipoInimigo,Stream), Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}
		else
		{
			TSubclassOf<AInimigo> InimigoNaoRandomico;
			

			switch (Dificuldade) //Escolher o inimigos baseado na dificuldade da sala.
			{
			case EDificuldadeSala::NORMAL:
				InimigoNaoRandomico = Spawner->InimigoNaoRandomicoNormal;
				break;
			case EDificuldadeSala::DIFICIL:
				InimigoNaoRandomico = Spawner->InimigoNaoRandomicoDificil;
				break;
			default:
				checkNoEntry();
				break;
			}

			if (InimigoNaoRandomico->IsValidLowLevelFast()) //Checando que a classe é não nula.
			{
				//Spawn do inimigo não randomicamente
				NovoInimigo = GetWorld()->SpawnActor<AInimigo>(InimigoNaoRandomico, Spawner->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}

		if (NovoInimigo->IsValidLowLevelFast()) //Checando se o inimigo gerado é valido.
		{
			NovoInimigo->SpawnDefaultController(); //Spawn do controlador do inimigo
			Inimigos.Add(NovoInimigo); //Adicionar o inimigo ao array de inimigos da sala.
			NovoInimigo->SalaPai = this; //Sala pai do inimigo é a sala atual.
		}

		AInimigosControlador* Controlador = Cast<AInimigosControlador>(NovoInimigo->GetController());

		if (Controlador->IsValidLowLevelFast()) //Checando a validade do controlador e fazendo com que a sala pai do controlador seja a sala atual.
		{
			Controlador->SalaPai = this;
		}
	}
}

TSubclassOf<AInimigo> ASala::GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade,FRandomStream& Stream)
{
	TSubclassOf<AInimigo> tipoInimigo = InimigoDificuldade[Stream.FRandRange(0, InimigoDificuldade.Num() - 1)]; //Usando um stream randomico para retornar o um inimigo dentro do array de inimigos de uma determinada dificuldade.

	return tipoInimigo;

}

void ASala::InimigosForamDerrotados()
{
	if (Inimigos.Num() == 0 && bSalaTemInimigos) //Apenas checar se a sala tem inimigos
	{
		for (const auto& Porta : Portas) //Destrancar todas as portas da sala.
		{
			Porta->DestrancarPorta();
		}
		
		//Desativando o delegate de overlap do trigger.
		bSalaTemInimigos = false;
		TriggerAtivarInimigos->OnComponentBeginOverlap.RemoveAll(this);
		TriggerAtivarInimigos->OnComponentEndOverlap.RemoveAll(this);
		DestrancarPortas(); //Evento para o blueprint das portas

		AJogador* jogador = Cast<AJogador>(GetWorld()->GetFirstPlayerController()->GetPawn());
		ASalasGerador* gerador = ASalasGerador::GetGeradorSalas(GetWorld());

		if (jogador->IsValidLowLevelFast() && gerador->IsValidLowLevelFast()) //Salvar o jogador e as salas.
		{
			jogador->SalvarJogador();
			gerador->SalvarSalas();
		}

	}

}

void ASala::TrancarPortas()
{
	for (const auto& Porta : Portas) //Trancar todas as portas
	{
		Porta->TrancarPorta();
	}

}

void ASala::AtivarInimigosTriggerOnOverlap(class AActor* OtherActor)
{
	AJogador* jogador = Cast<AJogador>(OtherActor);

	if (jogador->IsValidLowLevelFast() && bSalaTemInimigos) //Checando que quem faz o overlap é do tipo do jogador e que a sala tem inimigos.
	{
		for (auto const& Inimigo : Inimigos) //Ativando o controlador de cada inimigo na sala.
		{
			AInimigosControlador* controlador = Cast<AInimigosControlador>(Inimigo->GetController());

			if (controlador->IsValidLowLevelFast())
			{
				controlador->AtivarInimigo();
			}
		}

		AtualizarVidaInimigos(jogador);
		TrancarPortas(); //Trancando as portas
	}
}

void ASala::AtivarInimigosTriggerEndOverlap(class AActor* OtherActor)
{
	if (Cast<AJogador>(OtherActor) && bSalaTemInimigos) //Checando que quem faz o overlap é do tipo do jogador e que a sala tem inimigos.
	{
		for (auto const& Inimigo : Inimigos) //Desativando os controladores
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

	Sala->GetChildrenComponents(true, meshs); //Pegando as meshs que terão o seus materiais alterados.

	for (auto const& componente : meshs)
	{
		UInstancedStaticMeshComponent* instMesh = Cast<UInstancedStaticMeshComponent>(componente); 

		if (instMesh)
		{
			UMaterialInstanceDynamic* MID =  instMesh->CreateDynamicMaterialInstance(1); //Criando o material dinamico que tera a cor alterada.

			if (MID)
			{
				MID->SetVectorParameterValue("Base_Color", novaCor); //Alterando a cor do material.
			}
		}
	}
}

