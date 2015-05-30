// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/SalasGerador.h"
#include "Public/Salas/Corredor.h"
#include "Public/Salas/Sala.h"
#include "Public/Salas/Sala2P.h"
#include "Public/Salas/Sala2PDireita.h"
#include "Public/Salas/Sala2PEsquerda.h"
#include "Public/Salas/Sala3P.h"
#include "Public/Salas/Sala3PDireita.h"
#include "Public/Salas/Sala3PEsquerda.h"
#include "Public/Salas/Sala4P.h"


// Sets default values
ASalasGerador::ASalasGerador()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bSalaItemGerada = false;
	bSalaChaveGerada = false;
	bSalaBossGerada = false;

}

// Called when the game starts or when spawned
void ASalasGerador::BeginPlay()
{
	Super::BeginPlay();

}


FRotator ASalasGerador::GetDirecaoPorta(const FRotator& DirecaoSala, const EDirecaoPortas& Porta)
{

	FRotator ARetornar;

	switch (Porta)
	{
	case EDirecaoPortas::OESTE:
		ARetornar = DirecaoSala;
		break;
	case  EDirecaoPortas::NORTE:
		ARetornar = FRotationMatrix(DirecaoSala).GetScaledAxis(EAxis::Y).Rotation();
		break;
	case EDirecaoPortas::LESTE:
		ARetornar = -(DirecaoSala.Vector()).Rotation();
		break;
	case EDirecaoPortas::SUL:
		ARetornar = -(FRotationMatrix(DirecaoSala).GetScaledAxis(EAxis::Y)).Rotation();
		break;

	default:
		ARetornar = FRotator();
		break;
	}

	return ARetornar;
}

int32 ASalasGerador::GetNumPortasVazias()
{
	int32 vazias = 0;

	for (const auto& Sala : Salas)
	{
		if (!(*Sala).IsValidLowLevel())
		{
			vazias++;
		}
	}

	return vazias;
}

int32 ASalasGerador::UltimaSalaValida()
{

	int32 index = -1;

	for (int32 i = 0; i<Salas.Num(); i++)
	{
		if (Salas[i]->IsValidLowLevel())
		{
			index = i;
		}
		else
		{
			break;
		}
	}

	return index;
}

EDirecaoSala ASalasGerador::GetDirecaoSala(TSubclassOf<ASala> Classe)
{

	if ((*Classe)->IsChildOf(ASala2PDireita::StaticClass()) ||
		(*Classe)->IsChildOf(ASala3PDireita::StaticClass()))
	{
		return EDirecaoSala::DIREITA;
	}
	else if ((*Classe)->IsChildOf(ASala2PEsquerda::StaticClass()) ||
		(*Classe)->IsChildOf(ASala3PEsquerda::StaticClass()))
	{
		return EDirecaoSala::ESQUERDA;
	}
	else
	{
		return EDirecaoSala::NORMAL;
	}

}

ENumeroPortas ASalasGerador::GetNumeroPortas(TSubclassOf<ASala> Classe)
{
	if ((*Classe)->IsChildOf(ASala::StaticClass()))
	{
		return ENumeroPortas::UMA;
	}

	if ((*Classe)->IsChildOf(ASala2P::StaticClass()))
	{
		return ENumeroPortas::DUAS;
	}

	if ((*Classe)->IsChildOf(ASala3P::StaticClass()))
	{
		return ENumeroPortas::TRES;
	}

	return ENumeroPortas::QUATRO;

}


TArray< TEnumAsByte<EDirecaoPortas> > ASalasGerador::GerarArrayPortas(TSubclassOf<ASala> Classe)
{
	TArray<TEnumAsByte<EDirecaoPortas>> ARetornar;

	ENumeroPortas numPortas = GetNumeroPortas(Classe);

	EDirecaoSala tipo = GetDirecaoSala(Classe);

	switch (numPortas)
	{
	case ENumeroPortas::UMA:
		ARetornar.Add(EDirecaoPortas::OESTE);
		break;
	case ENumeroPortas::DUAS:

		switch (tipo)
		{
		case EDirecaoSala::NORMAL:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::LESTE);
			break;
		case EDirecaoSala::ESQUERDA:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::NORTE);
			break;
		case EDirecaoSala::DIREITA:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::SUL);
			break;
		}

		break;
	case ENumeroPortas::TRES:

		switch (tipo)
		{
		case EDirecaoSala::NORMAL:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::SUL);
			ARetornar.Add(EDirecaoPortas::NORTE);
			break;
		case EDirecaoSala::ESQUERDA:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::NORTE);
			ARetornar.Add(EDirecaoPortas::LESTE);
			break;
		case EDirecaoSala::DIREITA:
			ARetornar.Add(EDirecaoPortas::OESTE);
			ARetornar.Add(EDirecaoPortas::SUL);
			ARetornar.Add(EDirecaoPortas::LESTE);
			break;
		}

		break;
	case ENumeroPortas::QUATRO:
		ARetornar.Add(EDirecaoPortas::OESTE);
		ARetornar.Add(EDirecaoPortas::NORTE);
		ARetornar.Add(EDirecaoPortas::LESTE);
		ARetornar.Add(EDirecaoPortas::SUL);
		break;
	}

	return ARetornar;
}

FTransform ASalasGerador::GerarTransformSala(const ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * OffsetSala) + SalaAnterior->GetActorLocation();

	FRotator Rot = -(DirecaoPorta.Vector()).Rotation();

	return FTransform(Rot, Trans, EscalaPadraoSalas);
}

FTransform ASalasGerador::GerarTransformCorredor(const ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * OffsetCorredor) + SalaAnterior->GetActorLocation();

	FRotator Rot = -(DirecaoPorta.Vector()).Rotation();

	return FTransform(Rot, Trans, EscalaPadraoSalas);
}

TSubclassOf<ASala> ASalasGerador::SelecionarSala()
{
	int32 indice = 0;
	int32 limite = 0;

	int32 diferenca = NumeroSalas - Salas.Num();

	if (diferenca > 3)
	{
		limite = TiposSalas.Num() - 1;
	}
	else if (diferenca > 2)
	{
		limite = 4;
	}
	else if (diferenca > 1)
	{
		limite = 3;
	}
	else
	{
		FRandomStream Stream = FRandomStream(Seed);
		return TiposSalas[Stream.FRandRange(indice, limite)];
	}

	if (Salas.Num() <= MinNumSalas)
	{
		indice = 1;
	}

	FRandomStream Stream = FRandomStream(Seed);

	return TiposSalas[Stream.FRandRange(indice, limite)];
}

bool ASalasGerador::ColideNaDirecao(EDirecaoPortas Direcao, const FTransform& Trans)
{
	FVector Pos = (GetDirecaoPorta(Trans.Rotator(), Direcao).Vector() * OffsetSala) + Trans.GetLocation();

	static FName NAME_ChecarDirecao = FName(TEXT("ChecarDirecao"));

	FCollisionQueryParams SphereParams(NAME_ChecarDirecao, false, this);

	TArray<FOverlapResult> Overlaps;

	bool result = GetWorld()->OverlapMulti(Overlaps,
		Pos,
		FQuat::Identity,
		FCollisionShape::MakeSphere(100.0f), SphereParams,
		FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects));

	return result;
}


bool ASalasGerador::SalaEspecialGerada(TSubclassOf<ASala> SalaGerada)
{
	static int32 maxBoss = MaxNumSalas;
	static int32 minBoss = maxBoss - 4;
	static int32 maxChave = minBoss;
	static int32 minChave = maxChave - 3;
	static int32 minItem = 3;
	static int32 maxItem = 5;

	if (GetNumPortasVazias() > 1)
	{
		if (bSalaItemGerada)
		{
			if (bSalaChaveGerada)
			{
				if (bSalaBossGerada)
				{
					return false;
				}
				else
				{
					FRandomStream Stream(Seed);

					if (Salas.Num() >= Stream.FRandRange(minBoss, maxBoss))
					{
						SalaGerada = SalaBoss;
						bSalaBossGerada = true;
						return true;
					}
				}
			}
			else
			{
				FRandomStream Stream(Seed);

				if (Salas.Num() >= Stream.FRandRange(minChave, maxChave))
				{
					SalaGerada = SalaChave;
					bSalaChaveGerada = true;
					return true;
				}
			}

		}
		else
		{
			FRandomStream Stream(Seed);

			if (Salas.Num() >= Stream.FRandRange(minItem, maxItem))
			{
				SalaGerada = SalaItem;
				bSalaItemGerada = true;
				return true;
			}
		}
	}
	else
	{
		SalaGerada = SalaBoss;
		bSalaBossGerada = true;
		return true;
	}

	return false;
}

void ASalasGerador::SetNumSalas()
{
	FRandomStream Stream = FRandomStream(Seed);

	NumeroSalas = Stream.FRandRange(MinNumSalas, MaxNumSalas);

}

void ASalasGerador::GerarLevel(ASala* SalaAtual)
{
	SalaAtual->bVisitada = true;

	for (int32 i = SalaAtual->SalasConectadas.Num() + 1; i < (int32)SalaAtual->GetNumPortas(); i++)
	{
		GerarSala(SalaAtual, GetDirecaoPorta(SalaAtual->GetActorRotation(), (SalaAtual->GetDirecaoPortas())[i - 1]));
	}

	for (const auto& Sala : Salas)
	{
		if (!Sala->bVisitada)
		{
			GerarLevel(Sala);
		}
	}
}


void ASalasGerador::GerarSala(ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	TSubclassOf<ASala> salaGerada;

	static FTransform transSala = GerarTransformSala(SalaAnterior, DirecaoPorta);

	if (!SalaEspecialGerada(salaGerada))
	{
		salaGerada = SelecionarSala();
	}

	ImpedirColisao(salaGerada, transSala, DirecaoPorta);

	ASala* NovaSala = GetWorld()->SpawnActor<ASala>(salaGerada->StaticClass(), transSala.GetLocation(),transSala.GetRotation().Rotator());

	if (NovaSala->IsValidLowLevelFast())
	{
		NovaSala->SalasConectadas.Add(SalaAnterior);
		SalaAnterior->SalasConectadas.Add(NovaSala);
	}

	static FTransform transCorredor = GerarTransformCorredor(SalaAnterior, DirecaoPorta);

	ACorredor* NovoCorredor = GetWorld()->SpawnActor<ACorredor>(ACorredor::StaticClass(), transCorredor.GetLocation(), transCorredor.GetRotation().Rotator());

	if (!NovoCorredor->IsValidLowLevelFast())
	{
		//WARNING
	}

	if (NovaSala->GetNumPortas() > ENumeroPortas::UMA)
	{
		Salas.Reserve(Salas.Num() - 1 + (int32)NovaSala->GetNumPortas());
	}

	Salas[UltimaSalaValida() + 1] = NovaSala;
	

}

void ASalasGerador::ImpedirColisao(TSubclassOf<ASala> SalaGerada, const FTransform& Trans, const FRotator& DirecaoPorta)
{
	ENumeroPortas numPortas = GetNumeroPortas(SalaGerada);
	bool colide = false;

	do
	{
		switch (numPortas)
		{
		case ENumeroPortas::DUAS:

			switch (GetDirecaoSala(SalaGerada))
			{
			case EDirecaoSala::NORMAL:
				colide = false;
				if (ColideNaDirecao(EDirecaoPortas::LESTE, Trans))
				{
					SalaGerada = ASala2PEsquerda::StaticClass();
					colide = true;
				}
				break;
			case  EDirecaoSala::ESQUERDA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPortas::NORTE, Trans))
				{
					SalaGerada = ASala2PDireita::StaticClass();
					colide = true;
				}
				break;
			case EDirecaoSala::DIREITA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPortas::SUL, Trans))
				{
					SalaGerada = ASala::StaticClass();
					colide = true;
				}
				break;
			}

			break;
		case ENumeroPortas::TRES:
			colide = false;

			for (int32 i = 1; i <= 2; i++)
			{
				if (ColideNaDirecao(GerarArrayPortas(SalaGerada)[i], Trans))
				{
					switch (GetDirecaoSala(SalaGerada))
					{
					case EDirecaoSala::NORMAL:
						SalaGerada = ASala3PEsquerda::StaticClass();
						break;
					case EDirecaoSala::ESQUERDA:
						SalaGerada = ASala3PDireita::StaticClass();
						break;
					case EDirecaoSala::DIREITA:
						SalaGerada = ASala2P::StaticClass();
						break;
					}

					colide = true;
					break;
				}
			}
			break;
		case ENumeroPortas::QUATRO:
			colide = false;

			for (int32 i = 1; i <= 3; i++)
			{
				if (ColideNaDirecao(GerarArrayPortas(SalaGerada)[i], Trans))
				{
					SalaGerada = ASala3P::StaticClass();
					colide = true;
					break;
				}
			}
			break;
		}

	} while (!colide);

}

