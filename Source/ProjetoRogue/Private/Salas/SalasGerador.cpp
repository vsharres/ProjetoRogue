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
	Salas.Empty();
	bSalaItemGerada = false;
	bSalaChaveGerada = false;
	bSalaBossGerada = false;

}

void ASalasGerador::Inicializar(ASala* Inicial)
{
	SetNumSalas();

	Salas.Add(Inicial);
	Salas.Add(NULL);

	GerarLevel(Inicial);
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

	for (int32 i = 0; i < Salas.Num(); i++)
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

FTransform ASalasGerador::GerarTransformSala(const ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * ((ASala*)SalaGerada->GetDefaultObject(true))->GetOffset()) + SalaAnterior->GetActorLocation();

	FRotator Rot = (-DirecaoPorta.Vector()).Rotation();

	return FTransform(Rot, Trans, ((ASala*)SalaGerada->GetDefaultObject(true))->GetEscala());
}

FTransform ASalasGerador::GerarTransformCorredor(const ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * ((ACorredor*)ACorredor::StaticClass()->GetDefaultObject(true))->GetOffset()) + SalaAnterior->GetActorLocation();

	FRotator Rot = (-DirecaoPorta.Vector()).Rotation();

	return FTransform(Rot, Trans, ((ACorredor*)ACorredor::StaticClass()->GetDefaultObject(true))->GetEscala());
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
	ASala* sala = (ASala*)SalaGerada->GetDefaultObject();
	FVector Pos = (GetDirecaoPorta(Trans.Rotator(), Direcao).Vector() * sala->GetOffset()) + Trans.GetLocation();

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


bool ASalasGerador::SalaEspecialGerada()
{
	static int32 maxBoss = MaxNumSalas;
	static int32 minBoss = maxBoss - 4;
	static int32 maxChave = minBoss;
	static int32 minChave = maxChave - 3;
	static int32 minItem = 3;
	static int32 maxItem = 5;

	if (GetNumPortasVazias() > 1 || Salas.Num() < MinNumSalas)
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

	for (int32 i = SalaAtual->SalasConectadas.Num() + 1; i <= (int32)SalaAtual->GetNumPortas(); i++)
	{
		GerarSala(SalaAtual, GetDirecaoPorta(SalaAtual->GetActorRotation(), (SalaAtual->GetArrayPortas())[i - 1]));
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
	SalaGerada = nullptr;

	if (!SalaEspecialGerada())
	{
		SalaGerada = SelecionarSala();
	}

	FTransform transSala = GerarTransformSala(SalaAnterior, DirecaoPorta);

	ImpedirColisao(transSala, DirecaoPorta);

	ASala* NovaSala = GetWorld()->SpawnActor<ASala>(SalaGerada, transSala.GetLocation(), transSala.GetRotation().Rotator());

	if (NovaSala->IsValidLowLevelFast())
	{
		NovaSala->SalasConectadas.Add(SalaAnterior);
		SalaAnterior->SalasConectadas.Add(NovaSala);
	}

	FTransform transCorredor = GerarTransformCorredor(SalaAnterior, DirecaoPorta);

	ACorredor* NovoCorredor = GetWorld()->SpawnActor<ACorredor>(Corredor, transCorredor.GetLocation(), transCorredor.GetRotation().Rotator());

	if (!NovoCorredor->IsValidLowLevelFast())
	{
		//WARNING
	}

	if (NovaSala->GetNumPortas() > ENumeroPortas::UMA)
	{
		Salas.AddZeroed((int32)NovaSala->GetNumPortas() - 1);
	}

	Salas[UltimaSalaValida() + 1] = NovaSala;


}

void ASalasGerador::ImpedirColisao( const FTransform& Trans, const FRotator& DirecaoPorta)
{
	ASala* sala = (ASala*)SalaGerada->GetDefaultObject();

	ENumeroPortas numPortas = sala->GetNumPortas();
	bool colide = false;

	do
	{
		switch (numPortas)
		{
		case ENumeroPortas::DUAS:

			switch (sala->GetDirecao())
			{
			case EDirecaoSala::PADRAO:
				colide = false;
				if (ColideNaDirecao( EDirecaoPortas::LESTE, Trans))
				{
					SalaGerada = TiposSalas[2];
					colide = true;
				}
				break;
			case  EDirecaoSala::ESQUERDA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPortas::NORTE, Trans))
				{
					SalaGerada = TiposSalas[3];
					colide = true;
				}
				break;
			case EDirecaoSala::DIREITA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPortas::SUL, Trans))
				{
					SalaGerada = TiposSalas[0];
					colide = true;
				}
				break;
			}

			break;
		case ENumeroPortas::TRES:
			colide = false;

			for (int32 i = 1; i <= 2; i++)
			{
				if (ColideNaDirecao(sala->GetArrayPortas()[i], Trans))
				{
					switch (sala->GetDirecao())
					{
					case EDirecaoSala::PADRAO:
						SalaGerada = TiposSalas[5];
						break;
					case EDirecaoSala::ESQUERDA:
						SalaGerada = TiposSalas[6];
						break;
					case EDirecaoSala::DIREITA:
						SalaGerada = TiposSalas[1];
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
				if (ColideNaDirecao( sala->GetArrayPortas()[i], Trans))
				{
					SalaGerada = TiposSalas[4];
					colide = true;
					break;
				}
			}
			break;
		}

	} while (colide);

}

