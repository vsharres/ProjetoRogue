// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "SalasGerador.h"
#include "Corredor.h"
#include "CorredorLoja.h"
#include "Sala.h"
#include "Sala2P.h"
#include "Sala2PDireita.h"
#include "Sala2PEsquerda.h"
#include "Sala3P.h"
#include "Sala3PDireita.h"
#include "Sala3PEsquerda.h"
#include "Sala4P.h"

ASalasGerador::ASalasGerador()
{
	//Inicizalizando as propriedades.
	PrimaryActorTick.bCanEverTick = false;
	IndexSala2P = 1;
	IndexSala3P = 2;
	IndexSala4P = 3;
	Salas.Empty();
	PosSalas.Empty();
	UltimasSalasGeradas.Empty();
	bSalaItemGerada = false;
	bSalaChaveGerada = false;
	bSalaBossGerada = false;
	bCorredorLojaGerado = false;
	MinNumSalas = 5;
	MaxNumSalas = 10;

	ComprimentoMax = 100000.0f;
	LarguraMax = 100000.0f;

}

ASalasGerador* ASalasGerador::GetGeradorSalas(UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject); //Ponteiro ao UWorld atual, para encontrar o gerador de salas.
		if (World != nullptr)
		{
			for (TActorIterator<ASalasGerador> ActorItr(World); ActorItr; ++ActorItr) //Iterando sobre todos os atores até encontrar o gerador de salas.
			{
				if ((*ActorItr))
				{
					return *ActorItr;
				}
			}
		}
	}

	return nullptr;
}

void ASalasGerador::Inicializar(ASala* Inicial, int32 NovoSeed, int32 levelAtual)
{
	this->Seed = NovoSeed; 
	StreamGeracao = FRandomStream(NovoSeed); //Inicializando o stream randomico com o novo seed.

	SetNumSalas(levelAtual); //Set do num de salas a ser gerado.

	//Adicionando a sala inicial ao array de salas.
	Salas.Add(Inicial); 
	Salas.Add(NULL);

	AdicionarAoArrayPortas(Inicial);

	AProtuXGameMode* game = Cast<AProtuXGameMode>(GetWorld()->GetAuthGameMode());

	if (!game->bNovoJogo && !game->bNaoSalvar) //Se não for um novo jogo, fazer o load das salas.
	{
		CarregarSalas();
	}

	GerarLevel(Inicial); //Gerar o level em si

	GeracaoTerminada(); //Evento para o blueprint.
}


FRotator ASalasGerador::GetDirecaoPorta(const FRotator DirecaoSala, const EDirecaoPorta& Porta)
{

	FRotator ARetornar;
	FVector vec;

	switch (Porta) //escolhendo qual porta terá a sua rotação retornada.
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
	
	//Contar o número de salas nulas dentro do array de salas, sabendo assim quantas salas ainda podem ser geradas.
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
	//Encontrar a última sala válida.
	for (int32 i = 0; i < Salas.Num(); i++)
	{
		if (Salas[i])
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

FTransform ASalasGerador::GerarTransformSala(ASala* SalaAnterior, const FRotator DirecaoPorta)
{
	//Para determinar o transform da proxima sala, usamos a direção da porta que vai estar conecatada a sala, o offset da sala a ser gerada, o offset da sala anterior e o offset do corredor.
	FVector Trans = (DirecaoPorta.Vector() * (((ASala*)SalaGerada->GetDefaultObject(true))->GetOffset() + SalaAnterior->GetOffset() + (1150.0f * 2) )) + SalaAnterior->GetActorLocation();
	
	//Rodar a sala para ficar virada a porta.
	FVector dir = -(DirecaoPorta.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans, ((ASala*)SalaGerada->GetDefaultObject(true))->GetEscala());
}

FTransform ASalasGerador::GerarTransformCorredor(ASala* SalaAnterior, const FRotator DirecaoPorta)
{
	//Parar determinar o transform do corredor, usamos a direção da porta com o offset da sala anterior e o offset do corredor em si.
	FVector Trans = (DirecaoPorta.Vector() * (1150.0f + SalaAnterior->GetOffset())) + SalaAnterior->GetActorLocation();

	//Rodar o corredor para ficar virada a porta.
	FVector dir = -(DirecaoPorta.Vector());
	FRotator Rot = dir.Rotation();

	return FTransform(Rot, Trans);
}

TSubclassOf<ASala> ASalasGerador::SelecionarSala(ASala* SalaAnterior)
{
	TSubclassOf<ASala> retornar; //Sala a ser selecionada

	int32 indice = 0; //Indice mínimo dentro do array de salas.
	int32 limite = 0; //Indice máximo dentro do array de salas.

	int32 diferenca = NumeroSalas - Salas.Num(); //Saber a diferença entre o número de salas já geradas e o quantas ainda devem ser.

	if (diferenca == 0) //Se o número é igual, apenas a sala com 1 porta pode ser gerada.
	{
		indice = 0;
		limite = 0;

	}
	else if (diferenca == 1) //Se a diferença é igual a 1, apenas a sala com 2 portas pode ser gerada.
	{
		indice = IndexSala2P;
		limite = IndexSala2P;
	}
	else if (diferenca == 2) //Se a diferença é igual a 2, apenas a sala com 3 portas pode ser gerada.
	{
		indice = IndexSala3P;
		limite = IndexSala3P;
	}
	else if (diferenca == 3) //Se a diferença é igual a 4, apenas a sala com 4 portas pode ser gerada.
	{
		indice = IndexSala4P;
		limite = IndexSala4P;
	}
	else //Caso contrario, qualquer sala que tenha mais de 1 porta pode ser gerada.
	{

		indice = IndexSala2P;
		limite = TiposSalas.Num() - 1;

	}

	retornar = TiposSalas[StreamGeracao.FRandRange(indice, limite)]; //Escolher randomicamente dentre as salas que podem ser escolhidas.

	return retornar;
}

bool ASalasGerador::ColideNaDirecao(EDirecaoPorta Direcao, const FTransform& Trans)
{
	ASala* sala = (ASala*)SalaGerada->GetDefaultObject();
	FVector Pos = (GetDirecaoPorta(Trans.Rotator(), Direcao).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + Trans.GetLocation(); //Get o transformo da sala que vai ser gerada para testar colisao.

	bool result = EstaNoArrayDePosicoes(Pos);


	return result;
}

void ASalasGerador::CarregarSalas()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));
	
	//Criar o objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex)); 

	if (SaveInst->IsValidLowLevelFast() && !SaveInst->bNovoJogo) //Checar validade de ponteiro.
	{
		//Atualizar as propriedadas do gerador com as do save.
		this->Seed = SaveInst->Seed;
		this->MaxNumSalas = SaveInst->MaxNumSalas;
		this->MinNumSalas = SaveInst->MinNumSalas;
		this->SalasCarregadas.Empty();
		this->SalasCarregadas = SaveInst->SalasComInimigos;

	}
}

void ASalasGerador::SalvarSalas()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	if (!gameMode || gameMode->bNaoSalvar)
		return;

	//Criar o objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	if (!UGameplayStatics::DoesSaveGameExist(SaveInst->SaveSlot, SaveInst->Userindex)) //Checar se o savegame já existe, e caso não, criar um novo.
	{
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst->IsValidLowLevelFast()) //Checar validade de ponteiro.
	{
		//Atulizar as propriedades do save com as propriedades do gerador.
		SaveInst->Seed = this->Seed;
		SaveInst->MaxNumSalas = this->MaxNumSalas;
		SaveInst->MinNumSalas = this->MinNumSalas;
		SaveInst->SalasComInimigos.Empty();

		for (const auto& Sala : Salas) //Atulizar cada sala que teve os seus inimigos já derrotados
		{
			SaveInst->SalasComInimigos.Add(Sala->bSalaTemInimigos);
		}
		
		//Salvar
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void ASalasGerador::GerarSalaEspecial()
{
	if (((ASala*)SalaGerada->GetDefaultObject())->GetNumPortas() == ENumeroPortas::UMA) //Apenas selecionar salas especiais para o caso de salas com 1 porta.
	{

		int32 prob = StreamGeracao.FRandRange(0, 100); //Probablidade de gerar um tipo de sala.

		if (!bSalaItemGerada &&
			(prob > 66 || GetNumPortasVazias() == 3 && Salas.Num() == NumeroSalas)) //Gerar sala do item
		{
			SalaGerada = SalaItem;
			bSalaItemGerada = true;
			return;
		}

		if (!bSalaChaveGerada &&
			(prob > 33 || GetNumPortasVazias() == 2 && Salas.Num() == NumeroSalas)) //Gerar sala da chave
		{
			SalaGerada = SalaChave;
			bSalaChaveGerada = true;
			return;
		}

		if (!bSalaBossGerada &&
			(prob < 33 || GetNumPortasVazias() == 1 && Salas.Num() == NumeroSalas)) //Gerar sala do boss.
		{
			SalaGerada = SalaBoss;
			bSalaBossGerada = true;
			return;
		}

	}
}

bool ASalasGerador::EstaNoArrayDePosicoes(const FVector& pos)
{
	float tolerancia = 800.0f; //Tolerancia para comparar as posições
	for (const auto& position : PosSalas) //Comparar a pos com todas as salas dentro do array.
	{
		if (FMath::Abs(pos.X - position.X) <= tolerancia && FMath::Abs(pos.Y - position.Y) <= tolerancia)
		{
			return true;
		}
		else if (pos.X > SalaInicial->GetActorLocation().X + ComprimentoMax ||
			pos.X < SalaInicial->GetActorLocation().X - ComprimentoMax ||
			pos.Y > SalaInicial->GetActorLocation().Y + LarguraMax / 2 ||
			pos.Y < SalaInicial->GetActorLocation().Y - LarguraMax / 2)
		{
			return true;
		}
	}

	return false;
}

void ASalasGerador::SetNumSalas(int32 levelAtual)
{
	if (MinNumSalas > MaxNumSalas)
	{
		MinNumSalas = MaxNumSalas;
	}

	NumeroSalas = StreamGeracao.FRandRange(MinNumSalas, MaxNumSalas) + (levelAtual * 2); //Aumentar o número de salas de acordo com o level atual.

}

void ASalasGerador::AdicionarAoArrayPortas(ASala* sala)
{
	ENumeroPortas numPortas = sala->GetNumPortas(); //Pegar o numero de portas e adicionar ao array de portas da sala.

	switch (numPortas) //Para cada número de portas o padro de portas é diferente.
	{
	case ENumeroPortas::UMA:
		//PosSalas.Add(sala->GetActorLocation());
		break;
	case ENumeroPortas::DUAS:

		switch (sala->GetDirecao()) //Cada tipo de sala de um determinado número de portas tem um padrão diferente de direção das portas.
		{
		case EFormatoSala::PADRAO:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		case  EFormatoSala::ESQUERDA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		case EFormatoSala::DIREITA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		}
		break;

	case ENumeroPortas::TRES:
		switch (sala->GetDirecao())
		{
		case EFormatoSala::PADRAO:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		case  EFormatoSala::ESQUERDA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		case EFormatoSala::DIREITA:
			PosSalas.Add(sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
			break;
		}
		break;

	case ENumeroPortas::QUATRO:
		PosSalas.Add(sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::NORTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::LESTE).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
		PosSalas.Add((GetDirecaoPorta(sala->GetActorRotation(), EDirecaoPorta::SUL).Vector() * (sala->GetOffset() + (1150.0f * 2) + 1748.0f)) + sala->GetActorLocation());
		break;

	}
}

void ASalasGerador::GerarLevel_Implementation(ASala* SalaAtual)
{
	SalaAtual->bVisitada = true; //Sala atual foi visitada

	for (int32 i = SalaAtual->SalasConectadas.Num() + 1; i <= (int32)SalaAtual->GetNumPortas(); i++) //Loop em todas as salas geradas.
	{
		if (SalaAtual->SalasConectadas.Num() <= (int32)SalaAtual->GetNumPortas())
		{
			ASala* sala = GerarSala(SalaAtual, GetDirecaoPorta(SalaAtual->GetActorRotation(), (SalaAtual->GetArrayPortas())[i - 1])); //Gerar uma nova sala conectada a sala atual numa determinada porta.

			if (!sala->bVisitada) //Se a sala gerada não foi visitada, recursivamente gerar uma nova sala.
			{
				GerarLevel(sala);
			}
		}
	}
}


ASala* ASalasGerador::GerarSala(ASala* SalaAnterior, const FRotator& DirecaoPorta)
{
	SalaGerada = NULL;

	SalaGerada = SelecionarSala(SalaAnterior); //Selecionar sala a ser gerada.

	GerarSalaEspecial(); //Checar se a sala pode ser transformada numa sala especial.

	FTransform transSala = GerarTransformSala(SalaAnterior, DirecaoPorta); //Gerar o transform da nova sala.

	ImpedirColisao(transSala, DirecaoPorta); //Mudar o tipo da sala se a sala a ser gerada colide com alguma sala já existente.
	
	//Spawn da nova sala.
	ASala* NovaSala = GetWorld()->SpawnActor<ASala>(SalaGerada, transSala.GetLocation(), transSala.GetRotation().Rotator());

	if (NovaSala->IsValidLowLevelFast())
	{
		NovaSala->SetActorScale3D(NovaSala->GetEscala()); //Mudar escala da sala.
		NovaSala->SalasConectadas.Add(SalaAnterior); //Conectar a sala gerada a sala anterior.
		SalaAnterior->SalasConectadas.Add(NovaSala);
		UltimasSalasGeradas.Add(SalaGerada);

	}

	GerarCorredor(SalaAnterior, DirecaoPorta); //Gerar o corredor que conecta as salas.

	if (NovaSala->GetNumPortas() > ENumeroPortas::UMA) //Se a sala gerada tem mais de 1 porta, adicionar ao array de salas o número necessários de espaços para as salas que serão conectadas a sala gerada. ( por exemplo uma sala de 4 portas precisa da sala anterior e mais 3 salas para serem conectadas)
	{
		Salas.AddZeroed((int32)NovaSala->GetNumPortas() - 1);
	}

	Salas[UltimaSalaValida() + 1] = NovaSala; //Nova sala é a ultima sala gerada.

	AdicionarAoArrayPortas(NovaSala); //Adicionar a nova sala ao array de portas.

	if (SalasCarregadas.Num() >= Salas.Num()) //Checar se o level foi carregado ou se é um novo level.
	{
		NovaSala->bSalaTemInimigos = SalasCarregadas[Salas.Find(NovaSala)]; //Atulizar o estado dos inimigos.
	}

	NovaSala->SpawnInimigos(StreamGeracao); //Fazer o spawn dos inimigos na sala.

	UE_LOG(LogTemp, Warning, TEXT(" Sala nome: %s numero: %d"), *NovaSala->GetName(), Salas.Num());

	return NovaSala;
}

void ASalasGerador::GerarCorredor(ASala* SalaAnterior, const FRotator& DirecaoPorta)
{

	FTransform transCorredor = GerarTransformCorredor(SalaAnterior, DirecaoPorta); //Gerar o transform do corredor.

	int32 Valor = StreamGeracao.FRandRange(0, 100); //Probablidade de gerar o corredor com a loja
	
	//Se a probablidade for alta, e a loja ainda nao foi gerada, ou se a última sala gerada foi a do boss, fazer o spawn da loja
	if ((Valor >= 70 && !bCorredorLojaGerado) ||
		(!bCorredorLojaGerado && ((ASala*)SalaGerada->GetDefaultObject(true))->GetTipo() == ETipoSala::BOSS))
	{
		ACorredorLoja* NovoCorredor = GetWorld()->SpawnActor<ACorredorLoja>(CorredorLoja, transCorredor.GetLocation(), transCorredor.GetRotation().Rotator());
		NovoCorredor->SetActorScale3D(NovoCorredor->GetEscala());
		bCorredorLojaGerado = true;
	}
	else
	{
		//Spawn do corredor normal.
		ACorredor* NovoCorredor = GetWorld()->SpawnActor<ACorredor>(TiposCorredores[StreamGeracao.FRandRange(0,TiposCorredores.Num()-1)], transCorredor.GetLocation(), transCorredor.GetRotation().Rotator());
		NovoCorredor->SetActorScale3D(NovoCorredor->GetEscala());
	}



}

void ASalasGerador::ImpedirColisao(const FTransform& Trans, const FRotator DirecaoPorta)
{
	bool colide = false;

	do //Checar cada direcao das salas para colisao, e caso colide, mudar o tipo de sala até encontrar um tipo de sala que não colida.
	{
		ASala* sala = (ASala*)SalaGerada->GetDefaultObject();
		ENumeroPortas numPortas = sala->GetNumPortas();

		switch (numPortas) //Para o número de portas da sala, um tipo de direcao difernte deve ser checado.
		{
		case ENumeroPortas::DUAS:

			switch (sala->GetDirecao()) //Checar para cada direcao e alterar a sala a ser gerada caso alguma colisao seja detectada.
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

