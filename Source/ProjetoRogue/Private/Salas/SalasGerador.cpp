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
	IndexSala2P = 1;
	IndexSala3P = 2;
	IndexSala4P = 3;
	Salas.Empty();
	PosSalas.Empty();
	UltimasSalasGeradas.Empty();
	bSalaItemGerada = false;
	bSalaChaveGerada = false;
	bSalaBossGerada = false;
	MinNumSalas = 5;
	MaxNumSalas = 30;

}

ASalasGerador::~ASalasGerador()
{
	Salas.Empty();
	PosSalas.Empty();
	UltimasSalasGeradas.Empty();
	SalaInicial = NULL;
}

void ASalasGerador::Inicializar(ASala* Inicial)
{
	SetNumSalas();

	Salas.Add(Inicial);
	Salas.Add(NULL);

	AdicionarAoArrayPortas(Inicial);

	GerarLevel(Inicial);
	GeracaoTerminada();
}


FRotator ASalasGerador::GetDirecaoPorta(const FRotator DirecaoSala, const EDirecaoPorta& Porta)
{

	FRotator ARetornar;
	FVector vec;

	switch (Porta)
	{
	case EDirecaoPorta::OESTE:
		ARetornar = DirecaoSala;
		break;
	case  EDirecaoPorta::NORTE:
		ARetornar = FRotationMatrix(DirecaoSala).GetScaledAxis(EAxis::Y).Rotation();
		break;
	case EDirecaoPorta::LESTE:
		vec = -(DirecaoSala.Vector());
		ARetornar = vec.Rotation();
		break;
	case EDirecaoPorta::SUL:
		vec = -(FRotationMatrix(DirecaoSala).GetScaledAxis(EAxis::Y));
		ARetornar = vec.Rotation();
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

FTransform ASalasGerador::GerarTransformSala(const ASala* SalaAnterior, const FRotator DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * ((ASala*)SalaGerada->GetDefaultObject(true))->GetOffset()) + SalaAnterior->GetActorLocation();

	FVector dir = -(DirecaoPorta.Vector());

	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans, ((ASala*)SalaGerada->GetDefaultObject(true))->GetEscala());
}

FTransform ASalasGerador::GerarTransformCorredor(const ASala* SalaAnterior, const FRotator DirecaoPorta)
{
	FVector Trans = (DirecaoPorta.Vector() * ((ACorredor*)ACorredor::StaticClass()->GetDefaultObject(true))->GetOffset()) + SalaAnterior->GetActorLocation();

	FVector dir = -(DirecaoPorta.Vector());

	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans, ((ACorredor*)ACorredor::StaticClass()->GetDefaultObject(true))->GetEscala());
}

TSubclassOf<ASala> ASalasGerador::SelecionarSala(const ASala* SalaAnterior)
{
	TSubclassOf<ASala> retornar;

	int32 indice = 0;
	int32 limite = 0;

	int32 diferenca = NumeroSalas - Salas.Num();

	if (diferenca == 0)
	{
		indice = 0;
		limite = 0;

	}
	else if (diferenca == 1)
	{
		indice = IndexSala2P;
		limite = IndexSala2P;
	}
	else if (diferenca == 2)
	{
		indice = IndexSala3P;
		limite = IndexSala3P;
	}
	else if (diferenca == 3)
	{
		indice = IndexSala4P;
		limite = IndexSala4P;
	}
	else
	{
		if (Salas.Num() < NumeroSalas)
		{
			indice = IndexSala2P;
			limite = TiposSalas.Num() - 1;
		}

		if (Salas.Num() >= 3 && !bSalaItemGerada)
		{
			indice = IndexSala3P;
			limite = TiposSalas.Num() - 1;

		}
		else if (Salas.Num() >= 5 && !bSalaChaveGerada)
		{
			indice = IndexSala4P;
			limite = TiposSalas.Num() - 1;
		}

	}

	FRandomStream Stream = FRandomStream(Seed);
	retornar = TiposSalas[Stream.FRandRange(indice, limite)];

	return retornar;
}

bool ASalasGerador::ColideNaDirecao(EDirecaoPorta Direcao, const FTransform& Trans)
{
	ASala* sala = (ASala*)SalaGerada->GetDefaultObject();
	FVector Pos = (GetDirecaoPorta(Trans.Rotator(), Direcao).Vector() * sala->GetOffset()) + Trans.GetLocation();

	bool result = EstaNoArrayDePosicoes(Pos);

	return result;
}

void ASalasGerador::GerarSalaEspecial()
{
	if (((ASala*)SalaGerada->GetDefaultObject())->GetNumPortas() == ENumeroPortas::UMA)
	{
		FRandomStream Stream(Seed);


		if (!bSalaItemGerada && 
			(UltimaSalaValida() >= Stream.FRandRange(MinNumSalas, NumeroSalas) ||
			GetNumPortasVazias() == 3 && Salas.Num() == NumeroSalas))
		{
			SalaGerada = SalaItem;
			bSalaItemGerada = true;
			return;
		}

		if (!bSalaChaveGerada && 
			(UltimaSalaValida() >= Stream.FRandRange(7, 9) ||
			GetNumPortasVazias() == 2 && Salas.Num() == NumeroSalas))
		{
			SalaGerada = SalaChave;
			bSalaChaveGerada = true;
			return;
		}

		if (!bSalaBossGerada && 
			(UltimaSalaValida() >= Stream.FRandRange(2, 6) ||
			GetNumPortasVazias() == 1 && Salas.Num() == NumeroSalas))
		{
			SalaGerada = SalaBoss;
			bSalaBossGerada = true;
			return;
		}

	}

}

bool ASalasGerador::EstaNoArrayDePosicoes(const FVector& pos)
{
	float tolerancia = 10.0f;
	for (const auto& position : PosSalas)
	{
		if (pos.X + tolerancia > position.X && pos.X - tolerancia < position.X &&
			pos.Y + tolerancia > position.Y && pos.Y - tolerancia < position.Y)
		{
			return true;
		}
	}

	return false;
}

void ASalasGerador::SetNumSalas()
{
	FRandomStream Stream = FRandomStream(Seed);

	if (MinNumSalas > MaxNumSalas)
	{
		MinNumSalas = MaxNumSalas;
	}

	NumeroSalas = Stream.FRandRange(MinNumSalas, MaxNumSalas);

}

void ASalasGerador::AdicionarAoArrayPortas(ASala* sala)
{
	ENumeroPortas numPortas = sala->GetNumPortas();

	switch (numPortas)
	{
	case ENumeroPortas::UMA:
		PosSalas.Add(sala->GetActorLocation());
		break;
	case ENumeroPortas::DUAS:

		switch (sala->GetDirecao())
		{
		case EFormatoSala::PADRAO:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		case  EFormatoSala::ESQUERDA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		case EFormatoSala::DIREITA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		}
		break;

	case ENumeroPortas::TRES:
		switch (sala->GetDirecao())
		{
		case EFormatoSala::PADRAO:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		case  EFormatoSala::ESQUERDA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		case EFormatoSala::DIREITA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
			break;
		}
		break;

	case ENumeroPortas::QUATRO:
		PosSalas.Add(sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * sala->GetOffset()) + sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * sala->GetOffset()) + sala->GetActorLocation());
		break;

	}
}

void ASalasGerador::GerarLevel(ASala* SalaAtual)
{
	SalaAtual->bVisitada = true;

	for (int32 i = SalaAtual->SalasConectadas.Num() + 1; i <= (int32)SalaAtual->GetNumPortas(); i++)
	{
		if (SalaAtual->SalasConectadas.Num() <= (int32)SalaAtual->GetNumPortas())
		{
			ASala* sala = GerarSala(SalaAtual, GetDirecaoPorta(SalaAtual->GetActorRotation(), (SalaAtual->GetArrayPortas())[i - 1]));

			if (!sala->bVisitada)
			{
				GerarLevel(sala);
			}
		}
	}
}


ASala* ASalasGerador::GerarSala(ASala* SalaAnterior, const FRotator DirecaoPorta)
{
	SalaGerada = nullptr;

	SalaGerada = SelecionarSala(SalaAnterior);

	GerarSalaEspecial();

	FTransform transSala = GerarTransformSala(SalaAnterior, DirecaoPorta);

	ImpedirColisao(transSala, DirecaoPorta);

	ASala* NovaSala = GetWorld()->SpawnActor<ASala>(SalaGerada, transSala.GetLocation(), transSala.GetRotation().Rotator());

	if (NovaSala->IsValidLowLevelFast())
	{
		NovaSala->SalasConectadas.Add(SalaAnterior);
		SalaAnterior->SalasConectadas.Add(NovaSala);
		UltimasSalasGeradas.Add(SalaGerada);
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

	AdicionarAoArrayPortas(NovaSala);

	UE_LOG(LogTemp, Warning, TEXT(" Sala nome: %s numero: %d"), *NovaSala->GetName(), Salas.Num());

	return NovaSala;
}

void ASalasGerador::ImpedirColisao(const FTransform& Trans, const FRotator DirecaoPorta)
{
	bool colide = false;

	do
	{
		ASala* sala = (ASala*)SalaGerada->GetDefaultObject();
		ENumeroPortas numPortas = sala->GetNumPortas();

		switch (numPortas)
		{
		case ENumeroPortas::DUAS:

			switch (sala->GetDirecao())
			{
			case EFormatoSala::PADRAO:
				colide = false;
				if (ColideNaDirecao(EDirecaoPorta::LESTE, Trans))
				{
					SalaGerada = TiposSalas[0];
					colide = true;
				}
				break;
			case  EFormatoSala::ESQUERDA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPorta::NORTE, Trans))
				{
					SalaGerada = TiposSalas[1];
					colide = true;
				}
				break;
			case EFormatoSala::DIREITA:
				colide = false;
				if (ColideNaDirecao(EDirecaoPorta::SUL, Trans))
				{
					SalaGerada = TiposSalas[2];
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
					case EFormatoSala::PADRAO:
						SalaGerada = TiposSalas[3];
						break;
					case EFormatoSala::ESQUERDA:
						SalaGerada = TiposSalas[4];
						break;
					case EFormatoSala::DIREITA:
						SalaGerada = TiposSalas[5];
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
				if (ColideNaDirecao(sala->GetArrayPortas()[i], Trans))
				{
					SalaGerada = TiposSalas[6];
					colide = true;
					break;
				}
			}
			break;
		default:
			colide = false;
			break;
		}

	} while (colide);

}

