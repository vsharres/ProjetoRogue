// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.h"
#include "SalasGerador.generated.h"

/*
*	Classe que representa o gerador de salas. O gerador é responsável por gerar o level, gerar a navigação e fazer o spawn dos inimigos.
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

	/* Index onde começam as salas com duas portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Salas")
		int32 IndexSala2P;

	/* Index onde começam as salas com três portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Salas")
		int32 IndexSala3P;

	/* Index onde começam as salas com quatro portas no array de salas. */
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

	/* Booleano que indica se o corredor com a loja já foi gerado. */
	UPROPERTY(VisibleAnywhere, Category = "Corredor")
		bool bCorredorLojaGerado;

	/* Booleano que indica se a sala do item já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaItemGerada;

	/* Booleano que indica se a sala da chave já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaChaveGerada;

	/* Booleano que indica se a sala do boss já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bSalaBossGerada;

	/* Sala que está sendo gerada atualmente. */
	UPROPERTY()
		TSubclassOf<ASala> SalaGerada;

	/* Array com as últimas salas geradas. */
	UPROPERTY()
		TArray<TSubclassOf<ASala>> UltimasSalasGeradas;

	/* Array com a posição das salas geradas. */
	UPROPERTY()
		TArray<FVector> PosSalas;

	/* Array para verificar se todas as salas foram carregadas de um save game. */
	UPROPERTY()
		TArray<bool> SalasCarregadas;

	/* Distância X máxima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float ComprimentoMax;

	/* Distância Y máxima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float LarguraMax;

public:

	/* Stream de geração randômica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gerador)
		FRandomStream StreamGeracao;

	/* Array com os tipos de salas que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<TSubclassOf<ASala>> TiposSalas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corredor")
		TArray<TSubclassOf<ACorredor>> TiposCorredores;

	/* Número máximo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumSalas;

	/* Número mínimo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumSalas;

	/* Seed de geração randômica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Ponteiro a sala inicial. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		ASala* SalaInicial;

	/* Número máximo de salas que podem ser geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<ASala*> Salas;
#pragma endregion PROPRIEDADES

#pragma region CONSTRUTOR
	/*Construtor Padrão. */
	ASalasGerador();
#pragma endregion CONSTRUTOR

#pragma region FUNÇÕES
public:

	/*
	* Função estática que get do gerador de salas. Função utilizada por outras classes para acessar o gerador de salas.
	* @param WordlContextObject - Contexto de geração da sala.
	* @return Ponteiro ao gerador de salas.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ASalasGerador* GetGeradorSalas(UObject* WorldContextObject);

	/*
	* Função de inicialização do gerador de salas, iniciando o processo de geração do level.
	* @param Inicial - Ponteiro a sala inicial.
	* @param Seed - Novo seed do gerador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void Inicializar(ASala* Inicial, int32 NovoSeed);

	/*
	* Função de get da rotação relativa de uma determinada porta com relação a sala e a direção da porta.
	* @param DirecaoSala - Rotação da sala.
	* @param Porta - Direção padrão da sala.
	* @return Rotação da porta com relação a sala.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		FRotator GetDirecaoPorta(const FRotator DirecaoSala, const EDirecaoPorta& Porta);

	/*
	* Função de get do número total de portas vazias dentro do array de salas.
	* @return O número de salas vazias.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 GetNumPortasVazias();

	/*
	* Função que retorna o índice da última sala válida dentro do array de salas.
	* @return O número do índice.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 UltimaSalaValida();

	/*
	* Função que gera o transforma da sala a ser gerada.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que está gerando a sala.
	* @return O transforma da sala a ser gerada.
	*/
	UFUNCTION()
		FTransform GerarTransformSala(ASala* SalaAnterior, const FRotator DirecaoPorta);

	/*
	* Função que gera o transforma do corredor a ser gerado.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que está gerando a sala.
	* @return O transforma do correodr a ser gerada.
	*/
	UFUNCTION()
		FTransform GerarTransformCorredor(ASala* SalaAnterior, const FRotator DirecaoPorta);

	/*
	* Função que seleciona a sala a ser gerada, esta função checa quais salas podem ser geradas e garante que salas especiais serão geradas.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @return Classe da sala a ser gerada.
	*/
	UFUNCTION()
		TSubclassOf<ASala> SelecionarSala(ASala* SalaAnterior);

	/*
	* Função que utiliza o seed para o set do número de salas a serem geradas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SetNumSalas();

	/*
	* Função que adiciona uma nova sala ao array de salas.
	* @param sala - Ponteiro a sala a ser adicionada
	*/
	UFUNCTION()
		void AdicionarAoArrayPortas(ASala* sala);

	/*
	* Função que gera o level com todas as salas, corredores e faz o spawn dos inimigos.
	* Esta função é utilizada recursivamente.
	* @param SalaAtual - Ponteiro a sala atual da geração.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void GerarLevel(ASala* SalaAtual);

	/*
	* Função que gera uma sala.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar a sala.
	* @return Ponteiro a sala gerada.
	*/
	UFUNCTION()
		ASala* GerarSala(ASala* SalaAnterior, const FRotator& DirecaoPorta);

	/*
	* Função que gera um corredor.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar o corredor.
	*/
	UFUNCTION()
		void GerarCorredor(ASala* SalaAnterior, const FRotator& DirecaoPorta);

	/*
	* Função que impede a colisão de uma nova sala com salas que já foram geradas e com os limites de geração.
	* @param Trans - transform da sala a ser gerada para checar a colisão.
	* @param DirecaoPorta - Rotação da porta que vai gerar a sala.
	*/
	UFUNCTION()
		void ImpedirColisao(const FTransform& Trans, const FRotator DirecaoPorta);

	/*
	* Função que gera uma sala especial.
	*/
	UFUNCTION()
		void GerarSalaEspecial();

	/*
	* Função que checa se uma posição está dentro do array de posições, esta função é usada para impedir colisões.
	* @param pos - Vetor da posição a ser testada.
	* @return true quando o vetor está no array de posições
	*/
	UFUNCTION()
		bool EstaNoArrayDePosicoes(const FVector& pos);

	/*
	* Função que checa se um transform colide com uma sala numa determinada direção
	* @param Trans - Transform a ser testado.
	* @param Direcao -	Direcao da porta que gerou o transform.
	* @return true quando o transform colide.
	*/
	UFUNCTION()
		bool ColideNaDirecao(EDirecaoPorta Direcao, const FTransform& Trans);

	/*
	* Evento que é disparado quando a geração foi terminada.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Sala")
		void GeracaoTerminada();

	/*
	* Função que carregar de um save game as salas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void CarregarSalas();

	/*
	* Função que salva as salas em um save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SalvarSalas();
#pragma endregion FUNÇÕES

};
