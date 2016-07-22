// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.generated.h"

/*
* Enumeração que representa a dificuldade de uma determinada sala.
*/
UENUM(BlueprintType)
enum class ERoomDifficulty : uint8
{
	NORMAL,
	HARD

};
/*
* Enumeração que representa o número de portas que uma sala possuí.
*/
UENUM(BlueprintType)
enum class ENumberDoors : uint8
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
};

/*
* Enumeração que representa a direção que as portas da sala podem ter.
*/
UENUM(BlueprintType)
enum class EDoorDirection : uint8
{
	WEST,
	NORTH,
	EAST,
	SOUTH,

};

/*
* Enumeração que representa o formato da sala, necessário para poder deduzir a direção e o número de portas
*/
UENUM(BlueprintType)
enum class ERoomShape : uint8
{
	STANDARD,
	LEFT,
	RIGHT

};

/*
* Enumeração que representa o tipo da sala, que é a funcionalidade básica da sala.
*/
UENUM(BlueprintType)
enum class ERoomType : uint8
{
	NORMAL,
	START,
	ITEM,
	KEY,
	BOSS

};

/*
*	Classe que representa uma das salas do jogo. As salas são presets que serão escolhidos durante a geração do level.
*	A sala padrão é uma sala com apenas uma porta na direção Oeste.
*/
UCLASS()
class PROTUX_API ARoom : public AActor
{
	GENERATED_BODY()

#pragma region Properties

protected:
	//SALA

	/* Direção que a sala aponta. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomShape RoomDirection;

	/* Tipo da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomType RoomType;

	/* Dificuldade da sala.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		ERoomDifficulty Difficulty;

	/* Escala padrão da sala que vai ser gerada, utilizado durante a geração da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		FVector RoomScale;

	/* Offset padrão da sala, que é utilizado para gerar o transform da sala durante a geração.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
		float RoomOffset;

	/* Componente de colisão para detectar quando o jogador se aproxima de uma sala para ativar os inimigos dentro da sala. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerEnemiesActivate;

	//PORTAS

	/* Número de portas da sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
		ENumberDoors NumberDoors;

	/* Array de portas da sala. */
	UPROPERTY(BlueprintReadWrite, Category = "Portas")
		TArray<class ADoor*> Doors;

	/* Array de direções das portas, o índice da direção da porta é o mesmo indice da porta no TArray Portas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		TArray < TEnumAsByte<EDoorDirection> > DoorsDirArray;

	//INIMIGOS

	/* Array de inimigos que estão na sala. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		TArray<class AEnemy*> Enemies;

	/* Array contendo as classes de inimigos normais que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AEnemy>> ListEnemiesNormal;

	/* Array contendo as classes de inimigos difíceis que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AEnemy>> ListEnemiesHard;

	//ITENS
	/* Array contendo as classes de itens que podem ser gerados pela sala. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Itens")
		TArray<TSubclassOf<class UItem>> PossibleItems;

public:

	/* Booleano indicando se a sala tem inimigos. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inimigos")
		bool bRoomHasEnemies;

	/* Array de salas que estão conectadas a esta sala. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
		TArray<ARoom*> ConectedRooms;

	/* Booleano usado durante a geração do level, indicando se a sala já foi visitada pelo algortimo de geração. */
	UPROPERTY(BlueprintReadWrite, Category = Sala)
		bool bVisited;
#pragma endregion Properties

#pragma region Constructor

public:
	/*
	* Constructor da Classe.
	*/
	ARoom(const FObjectInitializer& ObjectInitializer);

#pragma endregion Constructor

#pragma region Functions

public:

	/*
	* Função Get da escala padrão da sala.
	* @return FVector com a escala da sala.
	*/
	UFUNCTION()
		FVector GetRoomScale();

	/*
	* Função Get do Offset padrão da sala.
	* @return int32 com o Offset da sala.
	*/
	UFUNCTION()
		float GetRoomOffset() const;

	/*
	* Função Get do número de portas.
	* @return Enumerador ENumeroPortas com o número de portas da sala.
	*/
	UFUNCTION()
		ENumberDoors GetNumDoors();

	/*
	* Função Get da direção da sala.
	* @return Enumerador EFormatoSala com o formato da sala.
	*/
	UFUNCTION()
		ERoomShape GetRoomShape();

	/*
	* Função Get do tipo da sala.
	* @return Enumerador ETipoSala com o tipo da sala.
	*/
	UFUNCTION()
		ERoomType GetRoomType();

	/*
	* Função Get do Array de portas
	* @return TArray<TEnumAsByte<EDirecaoPorta>> com o array de portas da sala.
	*/
	UFUNCTION()
		TArray<TEnumAsByte<EDoorDirection>> GetArrayDoors();

	UFUNCTION()
		void SetOffset(float newOffset);

	UFUNCTION()
		void DeactivateTrigger();

	/*
	* Função que remove um inimigo do array de inimigos da sala.
	* @param inimigo -  Ponteiro AInimigo ao inimigo a ser retirado.
	*/
	UFUNCTION()
		void RemoveEnemy(AEnemy* enemy);

	/*
	* Evento que é disparado para fazer o spawn dos inimigos.
	* Este evento pode ser redefinido por blueprint para criar gerações espécíficas para salas específicas
	* @param Stream - Stream randômico de geração
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Spawn Inimigos", Keywords = "Spawn Inimigos"), Category = "Spawn")
		void SpawnEnemies(FRandomStream& Stream);
	virtual void SpawnEnemies_Implementation(FRandomStream& Stream);

	/*
	* Função Get do tipo de inimigo a ser gerado para um determinado seed e para um tipo de dificuldade.
	* O tipo resultante é gerado aleatoriamente de acordo com o seed de geração.
	* @param InimigosDificuldade - Array com a classe dos inimigos que podem ser gerados.
	* @param Stream - Stream randômico de geração
	* @return O tipo de inimigo a ser gerado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Tipo Inimigos", Keywords = "Get Tipo Inimigos"), Category = "Inimigos")
		TSubclassOf<AEnemy> GetEnemyType(const TArray <TSubclassOf<AEnemy>>& EnemyClassArray,FRandomStream& Stream);

	/*
	* Função a ser executada quando todos os inimigos da sala foram derrotados.
	*/
	UFUNCTION()
		void OnEnemiesDefeated();

	/*
	* Função a ser executada para trancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trancar Portas", Keywords = "Trancar Portas"), Category = "Room")
		void LockDoors();

	/*
	* Função a ser executada para destrancar todas as portas da sala.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Portas", Keywords = "Destrancar Portas"), Category = "Room")
		void UnlockDoors();
	/*
	* Evento para ativar o elevador da sala do boss.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Ativar Elevador", Keywords = "Ativar Elevador"), Category = "Room")
		void ActivateElevator();

	/*
		Evento para atualizar a barra de vida dos inimigos.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Sala)
		void UpdateEnemiesHealth(AProtuXPlayer* player);

	/*
	* Evento de overlap do trigger de ativação dos inimigos.
	* A assinatura da função segue a assinatura dos eventos do tipo OnComponentBeginOverlap.
	*/
	UFUNCTION(BlueprintCallable, Category = Sala)
		void ActivateEnemiesTriggerOnOverlap(class AActor* OtherActor);

	/*
	* Evento de overlap do trigger de desativação dos inimigos.
	* A assinatura da função segue a assinatura dos eventos do tipo OnComponentEndOverlap.
	*/
	UFUNCTION(BlueprintCallable, Category = Sala)
		 void ActivateEnemiesTriggerEndOverlap(class AActor* OtherActor);

	/*
	* Função para alterar a cor dos detalhes da sala, indicando quando uma sala teve seus inimigos derrotados.
	* @param novaCor - Nova cor da sala.
	* @param sala - Componente do ator que contem os mesh da sala que teram os seus materiais alterados.
	*/
	UFUNCTION(BlueprintCallable, Category = Glow)
		void ChangeRoomColor(FLinearColor newColor, USceneComponent* room);

	/*
	* Override do Tick da sala.
	*/
	virtual void Tick(float DeltaTime) override;

#pragma endregion Functions

};
