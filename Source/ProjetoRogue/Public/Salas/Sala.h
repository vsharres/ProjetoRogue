// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.generated.h"

/*
* Enumeração que representa a dificuldade de uma determinada sala.
*/
UENUM(BlueprintType)
enum class EDificuldadeSala : uint8
{
	FACIL,
	NORMAL,
	DIFICIL

};
/*
* Enumeração que representa o número de portas que uma sala possuí.
*/
UENUM(BlueprintType)
enum class ENumeroPortas : uint8
{
	ZERO,
	UMA,
	DUAS,
	TRES,
	QUATRO,
};

/*
* Enumeração que representa a direção que as portas da sala podem ter.
*/
UENUM(BlueprintType)
enum class EDirecaoPorta : uint8
{
	OESTE,
	NORTE,
	LESTE,
	SUL,

};

/*
* Enumeração que representa o formato da sala, necessário para poder deduzir a direção e o número de portas
*/
UENUM(BlueprintType)
enum class EFormatoSala : uint8
{
	PADRAO,
	ESQUERDA,
	DIREITA

};

/*
* Enumeração que representa o tipo da sala, que é a funcionalidade básica da sala.
*/
UENUM(BlueprintType)
enum class ETipoSala : uint8
{
	NORMAL,
	INICIO,
	ITEM,
	CHAVE,
	BOSS

};

/*
*	Classe que representa uma das salas do jogo. As salas são presets que serão escolhidos durante a geração do level.
*	A sala padrão é uma sala com apenas uma porta na direção Oeste.
*/
UCLASS()
class PROJETOROGUE_API ASala : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

protected:
	//SALA

	/* Direção que a sala aponta. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EFormatoSala DirecaoSala;

	/* Tipo da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		ETipoSala TipoSala;

	/* Dificuldade da sala.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EDificuldadeSala Dificuldade;
	/* Escala padrão da sala que vai ser gerada, utilizado durante a geração da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		FVector EscalaPadrao;

	/* Offset padrão da sala, que é utilizado para gerar o transform da sala durante a geração.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		float OffsetSala;

	/* Componente de colisão para detectar quando o jogador se aproxima de uma sala para ativar os inimigos dentro da sala. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerAtivarInimigos;

	//PORTAS

	/* Número de portas da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Portas")
		ENumeroPortas NumeroPortas;

	/* Array de portas da sala. */
	UPROPERTY(BlueprintReadWrite, Category = "Portas")
		TArray<class APorta*> Portas;

	/* Array de direções das portas, o índice da direção da porta é o mesmo indice da porta no TArray Portas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portas")
		TArray < TEnumAsByte<EDirecaoPorta> > DirecaoPortas;


	//INIMIGOS

	/* Booleano indicando se a sala tem inimigos ativados. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		bool bInimigosAtivos;

	/* Array de inimigos que estão na sala. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		TArray<class AInimigo*> Inimigos;

	/* Array contendo as classes de inimigos fáceis que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosFacil;

	/* Array contendo as classes de inimigos normais que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosNormal;

	/* Array contendo as classes de inimigos difíceis que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosDificil;

	//ITENS
	/* Array contendo as classes de itens que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Itens")
		TArray<TSubclassOf<class UItem>> PossiveisItens;

public:

	/* Booleano indicando se a sala tem inimigos. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inimigos")
		bool bSalaTemInimigos;

	/* Array de salas que estão conectadas a esta sala. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TArray<ASala*> SalasConectadas;

	/* Booleano usado durante a geração do level, indicando se a sala já foi visitada pelo algortimo de geração. */
	UPROPERTY()
		bool bVisitada;
#pragma endregion PROPRIEDADES

#pragma region CONSTRUTOR

public:
	/*
	* Constructor da Classe.
	*/
	ASala(const FObjectInitializer& ObjectInitializer);

#pragma endregion CONSTRUTOR

#pragma region FUNÇÕES

public:

	/*
	* Função Get da escala padrão da sala.
	* @return FVector com a escala da sala.
	*/
	UFUNCTION()
		FVector GetEscala();

	/*
	* Função Get do Offset padrão da sala.
	* @return int32 com o Offset da sala.
	*/
	UFUNCTION()
		float GetOffset() const;

	/*
	* Função Get do número de portas.
	* @return Enumerador ENumeroPortas com o número de portas da sala.
	*/
	UFUNCTION()
		ENumeroPortas GetNumPortas();

	/*
	* Função Get da direção da sala.
	* @return Enumerador EFormatoSala com o formato da sala.
	*/
	UFUNCTION()
		EFormatoSala GetDirecao();

	/*
	* Função Get do tipo da sala.
	* @return Enumerador ETipoSala com o tipo da sala.
	*/
	UFUNCTION()
		ETipoSala GetTipo();

	/*
	* Função Get do Array de portas
	* @return TArray<TEnumAsByte<EDirecaoPorta>> com o array de portas da sala.
	*/
	UFUNCTION()
		TArray<TEnumAsByte<EDirecaoPorta>> GetArrayPortas();

	UFUNCTION()
		void SetOffset(float novoOffset);

	/*
	* Função que remove um inimigo do array de inimigos da sala.
	* @param inimigo -  Ponteiro AInimigo ao inimigo a ser retirado.
	*/
	UFUNCTION()
		void RemoverInimigo(AInimigo* inimigo);

	/*
	* Evento que é disparado para fazer o spawn dos inimigos.
	* Este evento pode ser redefinido por blueprint para criar gerações espécíficas para salas específicas
	* @param Stream - Stream randômico de geração
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Spawn Inimigos", Keywords = "Spawn Inimigos"), Category = "Spawn")
		void SpawnInimigos(FRandomStream& Stream);
	virtual void SpawnInimigos_Implementation(FRandomStream& Stream);

	/*
	* Função Get do tipo de inimigo a ser gerado para um determinado seed e para um tipo de dificuldade.
	* O tipo resultante é gerado aleatoriamente de acordo com o seed de geração.
	* @param InimigosDificuldade - Array com inimigos possiveis a serem gerados.
	* @param Stream - Stream randômico de geração
	* @return O tipo de inimigo a ser gerado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Tipo Inimigos", Keywords = "Get Tipo Inimigos"), Category = "Inimigos")
		TSubclassOf<AInimigo> GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade,FRandomStream& Stream);

	/*
	* Função a ser executada quando todos os inimigos da sala foram derrotados.
	*/
	UFUNCTION()
		void InimigosForamDerrotados();

	/*
	* Função a ser executada para trancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trancar Portas", Keywords = "Trancar Portas"), Category = "Sala")
		void TrancarPortas();

	/*
	* Função a ser executada para destrancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Portas", Keywords = "Destrancar Portas"), Category = "Sala")
		void DestrancarPortas();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Ativar Elevador", Keywords = "Ativar Elevador"), Category = "Sala")
		void AtivarElevador();

	/*
	* Evento de overlap do trigger de ativação dos inimigos.
	* A assinatura da função segue a assinatura dos eventos do tipo OnComponentBeginOverlap.
	*/
	UFUNCTION()
		void AtivarInimigosTriggerOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Evento de overlap do trigger de desativação dos inimigos.
	* A assinatura da função segue a assinatura dos eventos do tipo OnComponentEndOverlap.
	*/
	UFUNCTION()
		void AtivarInimigosTriggerEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = Glow)
		void AlterarCorSala(FLinearColor novaCor, USceneComponent* Sala);

	/*
	* Override do Tick da sala.
	*/
	virtual void Tick(float DeltaTime) override;

	/*
	* Override do evento BeginPlay.
	*/
	virtual void BeginPlay() override;

#pragma endregion FUNÇÕES

};
