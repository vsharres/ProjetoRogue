// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.h"
#include "SalasGerador.generated.h"

/*
*	Classe que representa o gerador de salas. O gerador � respons�vel por gerar o level, gerar a naviga��o e fazer o spawn dos inimigos.
*/
UCLASS()
class PROJETOROGUE_API ASalasGerador : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES
private:

	/* Numero de salas a serem geradas. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		int32 NumeroSalas;

	/* Index onde come�am as salas com duas portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Salas")
		int32 IndexSala2P;

	/* Index onde come�am as salas com tr�s portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Salas")
		int32 IndexSala3P;

	/* Index onde come�am as salas com quatro portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "3"), Category = "Salas")
		int32 IndexSala4P;

	/* Classe da sala que gera o item no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<class ASala> SalaItem;

	/* Classe da sala que gera a chave da sala do boss no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ASala> SalaChave;

	/* Classe da sala que gera a chave da sala do boss no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ASala> SalaBoss;

	/* Classe do corredor da loja. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ACorredor> CorredorLoja;

	/* Booleano que indica se o corredor com a loja j� foi gerado. */
	UPROPERTY(VisibleAnywhere, Category = "Corredor")
		bool bCorredorLojaGerado;

	/* Booleano que indica se a sala do item j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaItemGerada;

	/* Booleano que indica se a sala da chave j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaChaveGerada;

	/* Booleano que indica se a sala do boss j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaBossGerada;

	/* Sala que est� sendo gerada atualmente. */
	UPROPERTY()
		TSubclassOf<ASala> SalaGerada;

	/* Array com as �ltimas salas geradas. */
	UPROPERTY()
		TArray<TSubclassOf<ASala>> UltimasSalasGeradas;

	/* Array com a posi��o das salas geradas. */
	UPROPERTY()
		TArray<FVector> PosSalas;

	/* Array para verificar se todas as salas foram carregadas de um save game. */
	UPROPERTY()
		TArray<bool> SalasCarregadas;

	/* Dist�ncia X m�xima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float ComprimentoMax;

	/* Dist�ncia Y m�xima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float LarguraMax;

public:

	/* Stream de gera��o rand�mica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gerador)
		FRandomStream StreamGeracao;

	/* Array com os tipos de salas que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<TSubclassOf<ASala>> TiposSalas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corredor")
		TArray<TSubclassOf<ACorredor>> TiposCorredores;

	/* N�mero m�ximo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumSalas;

	/* N�mero m�nimo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumSalas;

	/* Seed de gera��o rand�mica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Ponteiro a sala inicial. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		ASala* SalaInicial;

	/* N�mero m�ximo de salas que podem ser geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<ASala*> Salas;
#pragma endregion PROPRIEDADES

#pragma region CONSTRUTOR
	/*Construtor Padr�o. */
	ASalasGerador();
#pragma endregion CONSTRUTOR

#pragma region FUN��ES
public:

	/*
	* Fun��o est�tica que get do gerador de salas. Fun��o utilizada por outras classes para acessar o gerador de salas.
	* @param WordlContextObject - Contexto de gera��o da sala.
	* @return Ponteiro ao gerador de salas.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ASalasGerador* GetGeradorSalas(UObject* WorldContextObject);

	/*
	* Fun��o de inicializa��o do gerador de salas, iniciando o processo de gera��o do level.
	* @param Inicial - Ponteiro a sala inicial.
	* @param Seed - Novo seed do gerador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void Inicializar(ASala* Inicial, int32 NovoSeed);

	/*
	* Fun��o de get da rota��o relativa de uma determinada porta com rela��o a sala e a dire��o da porta.
	* @param DirecaoSala - Rota��o da sala.
	* @param Porta - Dire��o padr�o da sala.
	* @return Rota��o da porta com rela��o a sala.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		FRotator GetDirecaoPorta(const FRotator DirecaoSala, const EDirecaoPorta& Porta);

	/*
	* Fun��o de get do n�mero total de portas vazias dentro do array de salas.
	* @return O n�mero de salas vazias.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 GetNumPortasVazias();

	/*
	* Fun��o que retorna o �ndice da �ltima sala v�lida dentro do array de salas.
	* @return O n�mero do �ndice.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 UltimaSalaValida();

	/*
	* Fun��o que gera o transforma da sala a ser gerada.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que est� gerando a sala.
	* @return O transforma da sala a ser gerada.
	*/
	UFUNCTION()
		FTransform GerarTransformSala(ASala* SalaAnterior, const FRotator DirecaoPorta);

	/*
	* Fun��o que gera o transforma do corredor a ser gerado.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que est� gerando a sala.
	* @return O transforma do correodr a ser gerada.
	*/
	UFUNCTION()
		FTransform GerarTransformCorredor(ASala* SalaAnterior, const FRotator DirecaoPorta);

	/*
	* Fun��o que seleciona a sala a ser gerada, esta fun��o checa quais salas podem ser geradas e garante que salas especiais ser�o geradas.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @return Classe da sala a ser gerada.
	*/
	UFUNCTION()
		TSubclassOf<ASala> SelecionarSala(ASala* SalaAnterior);

	/*
	* Fun��o que utiliza o seed para o set do n�mero de salas a serem geradas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SetNumSalas();

	/*
	* Fun��o que adiciona uma nova sala ao array de salas.
	* @param sala - Ponteiro a sala a ser adicionada
	*/
	UFUNCTION()
		void AdicionarAoArrayPortas(ASala* sala);

	/*
	* Fun��o que gera o level com todas as salas, corredores e faz o spawn dos inimigos.
	* Esta fun��o � utilizada recursivamente.
	* @param SalaAtual - Ponteiro a sala atual da gera��o.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void GerarLevel(ASala* SalaAtual);

	/*
	* Fun��o que gera uma sala.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que vai gerar a sala.
	* @return Ponteiro a sala gerada.
	*/
	UFUNCTION()
		ASala* GerarSala(ASala* SalaAnterior, const FRotator& DirecaoPorta);

	/*
	* Fun��o que gera um corredor.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que vai gerar o corredor.
	*/
	UFUNCTION()
		void GerarCorredor(ASala* SalaAnterior, const FRotator& DirecaoPorta);

	/*
	* Fun��o que impede a colis�o de uma nova sala com salas que j� foram geradas e com os limites de gera��o.
	* @param Trans - transform da sala a ser gerada para checar a colis�o.
	* @param DirecaoPorta - Rota��o da porta que vai gerar a sala.
	*/
	UFUNCTION()
		void ImpedirColisao(const FTransform& Trans, const FRotator DirecaoPorta);

	/*
	* Fun��o que gera uma sala especial.
	*/
	UFUNCTION()
		void GerarSalaEspecial();

	/*
	* Fun��o que checa se uma posi��o est� dentro do array de posi��es, esta fun��o � usada para impedir colis�es.
	* @param pos - Vetor da posi��o a ser testada.
	* @return true quando o vetor est� no array de posi��es
	*/
	UFUNCTION()
		bool EstaNoArrayDePosicoes(const FVector& pos);

	/*
	* Fun��o que checa se um transform colide com uma sala numa determinada dire��o
	* @param Trans - Transform a ser testado.
	* @param Direcao -	Direcao da porta que gerou o transform.
	* @return true quando o transform colide.
	*/
	UFUNCTION()
		bool ColideNaDirecao(EDirecaoPorta Direcao, const FTransform& Trans);

	/*
	* Evento que � disparado quando a gera��o foi terminada.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Sala")
		void GeracaoTerminada();

	/*
	* Fun��o que carregar de um save game as salas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void CarregarSalas();

	/*
	* Fun��o que salva as salas em um save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SalvarSalas();
#pragma endregion FUN��ES

};
