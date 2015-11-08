// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.generated.h"

/*
* Enumera��o que representa a dificuldade de uma determinada sala.
*/
UENUM(BlueprintType)
enum class EDificuldadeSala : uint8
{
	FACIL,
	NORMAL,
	DIFICIL

};
/*
* Enumera��o que representa o n�mero de portas que uma sala possu�.
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
* Enumera��o que representa a dire��o que as portas da sala podem ter.
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
* Enumera��o que representa o formato da sala, necess�rio para poder deduzir a dire��o e o n�mero de portas
*/
UENUM(BlueprintType)
enum class EFormatoSala : uint8
{
	PADRAO,
	ESQUERDA,
	DIREITA

};

/*
* Enumera��o que representa o tipo da sala, que � a funcionalidade b�sica da sala.
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
*	Classe que representa uma das salas do jogo. As salas s�o presets que ser�o escolhidos durante a gera��o do level.
*	A sala padr�o � uma sala com apenas uma porta na dire��o Oeste.
*/
UCLASS()
class PROJETOROGUE_API ASala : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

protected:
	//SALA

	/* Dire��o que a sala aponta. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EFormatoSala DirecaoSala;

	/* Tipo da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		ETipoSala TipoSala;

	/* Dificuldade da sala.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EDificuldadeSala Dificuldade;
	/* Escala padr�o da sala que vai ser gerada, utilizado durante a gera��o da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		FVector EscalaPadrao;

	/* Offset padr�o da sala, que � utilizado para gerar o transform da sala durante a gera��o.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		float OffsetSala;

	/* Componente de colis�o para detectar quando o jogador se aproxima de uma sala para ativar os inimigos dentro da sala. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerAtivarInimigos;

	//PORTAS

	/* N�mero de portas da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Portas")
		ENumeroPortas NumeroPortas;

	/* Array de portas da sala. */
	UPROPERTY(BlueprintReadWrite, Category = "Portas")
		TArray<class APorta*> Portas;

	/* Array de dire��es das portas, o �ndice da dire��o da porta � o mesmo indice da porta no TArray Portas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portas")
		TArray < TEnumAsByte<EDirecaoPorta> > DirecaoPortas;


	//INIMIGOS

	/* Booleano indicando se a sala tem inimigos ativados. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		bool bInimigosAtivos;

	/* Array de inimigos que est�o na sala. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		TArray<class AInimigo*> Inimigos;

	/* Array contendo as classes de inimigos f�ceis que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosFacil;

	/* Array contendo as classes de inimigos normais que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosNormal;

	/* Array contendo as classes de inimigos dif�ceis que podem ser gerados pela sala. */
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

	/* Array de salas que est�o conectadas a esta sala. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TArray<ASala*> SalasConectadas;

	/* Booleano usado durante a gera��o do level, indicando se a sala j� foi visitada pelo algortimo de gera��o. */
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

#pragma region FUN��ES

public:

	/*
	* Fun��o Get da escala padr�o da sala.
	* @return FVector com a escala da sala.
	*/
	UFUNCTION()
		FVector GetEscala();

	/*
	* Fun��o Get do Offset padr�o da sala.
	* @return int32 com o Offset da sala.
	*/
	UFUNCTION()
		float GetOffset() const;

	/*
	* Fun��o Get do n�mero de portas.
	* @return Enumerador ENumeroPortas com o n�mero de portas da sala.
	*/
	UFUNCTION()
		ENumeroPortas GetNumPortas();

	/*
	* Fun��o Get da dire��o da sala.
	* @return Enumerador EFormatoSala com o formato da sala.
	*/
	UFUNCTION()
		EFormatoSala GetDirecao();

	/*
	* Fun��o Get do tipo da sala.
	* @return Enumerador ETipoSala com o tipo da sala.
	*/
	UFUNCTION()
		ETipoSala GetTipo();

	/*
	* Fun��o Get do Array de portas
	* @return TArray<TEnumAsByte<EDirecaoPorta>> com o array de portas da sala.
	*/
	UFUNCTION()
		TArray<TEnumAsByte<EDirecaoPorta>> GetArrayPortas();

	UFUNCTION()
		void SetOffset(float novoOffset);

	/*
	* Fun��o que remove um inimigo do array de inimigos da sala.
	* @param inimigo -  Ponteiro AInimigo ao inimigo a ser retirado.
	*/
	UFUNCTION()
		void RemoverInimigo(AInimigo* inimigo);

	/*
	* Evento que � disparado para fazer o spawn dos inimigos.
	* Este evento pode ser redefinido por blueprint para criar gera��es esp�c�ficas para salas espec�ficas
	* @param Stream - Stream rand�mico de gera��o
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Spawn Inimigos", Keywords = "Spawn Inimigos"), Category = "Spawn")
		void SpawnInimigos(FRandomStream& Stream);
	virtual void SpawnInimigos_Implementation(FRandomStream& Stream);

	/*
	* Fun��o Get do tipo de inimigo a ser gerado para um determinado seed e para um tipo de dificuldade.
	* O tipo resultante � gerado aleatoriamente de acordo com o seed de gera��o.
	* @param InimigosDificuldade - Array com inimigos possiveis a serem gerados.
	* @param Stream - Stream rand�mico de gera��o
	* @return O tipo de inimigo a ser gerado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Tipo Inimigos", Keywords = "Get Tipo Inimigos"), Category = "Inimigos")
		TSubclassOf<AInimigo> GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade,FRandomStream& Stream);

	/*
	* Fun��o a ser executada quando todos os inimigos da sala foram derrotados.
	*/
	UFUNCTION()
		void InimigosForamDerrotados();

	/*
	* Fun��o a ser executada para trancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trancar Portas", Keywords = "Trancar Portas"), Category = "Sala")
		void TrancarPortas();

	/*
	* Fun��o a ser executada para destrancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Portas", Keywords = "Destrancar Portas"), Category = "Sala")
		void DestrancarPortas();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Ativar Elevador", Keywords = "Ativar Elevador"), Category = "Sala")
		void AtivarElevador();

	/*
	* Evento de overlap do trigger de ativa��o dos inimigos.
	* A assinatura da fun��o segue a assinatura dos eventos do tipo OnComponentBeginOverlap.
	*/
	UFUNCTION()
		void AtivarInimigosTriggerOnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*
	* Evento de overlap do trigger de desativa��o dos inimigos.
	* A assinatura da fun��o segue a assinatura dos eventos do tipo OnComponentEndOverlap.
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

#pragma endregion FUN��ES

};
