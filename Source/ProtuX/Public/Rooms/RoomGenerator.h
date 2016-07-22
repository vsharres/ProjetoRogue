// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.h"
#include "RoomGenerator.generated.h"

/*
*	Classe que representa o gerador de salas. O gerador � respons�vel por gerar o level, gerar a naviga��o e fazer o spawn dos inimigos.
*/
UCLASS()
class PROTUX_API ARoomGenerator : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:

	/* Numero de salas a serem geradas. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		int32 NumGeneratedRooms;

	/* Index onde come�am as salas com duas portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Salas")
		int32 Room2DIndex;

	/* Index onde come�am as salas com tr�s portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Salas")
		int32 Room3DIndex;

	/* Index onde come�am as salas com quatro portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "3"), Category = "Salas")
		int32 Room4DIndex;

	/* Classe da sala que gera o item no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<class ARoom> ItemRoom;

	/* Classe da sala que gera a chave da sala do boss no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ARoom> KeyRoom;

	/* Classe da sala que gera a chave da sala do boss no level. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ARoom> BossRoom;

	/* Classe do corredor da loja. */
	UPROPERTY(EditDefaultsOnly, Category = "Salas")
		TSubclassOf<ACorridor> ShopCorridor;

	/* Booleano que indica se o corredor com a loja j� foi gerado. */
	UPROPERTY(VisibleAnywhere, Category = "Corredor")
		bool bIsShopSpawned;

	/* Booleano que indica se a sala do item j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bIsItemSpawned;

	/* Booleano que indica se a sala da chave j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bIsKeySpawned;

	/* Booleano que indica se a sala do boss j� foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bBossSpawned;

	/* Sala que est� sendo gerada atualmente. */
	UPROPERTY()
		TSubclassOf<ARoom> GeneratedRoom;

	/* Array com as �ltimas salas geradas. */
	UPROPERTY()
		TArray<TSubclassOf<ARoom>> PreviousGeneratedRooms;

	/* Array para verificar se todas as salas foram carregadas de um save game. */
	UPROPERTY()
		TArray<bool> LoadedRooms;

	/* Dist�ncia X m�xima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float MaxLength;

	/* Dist�ncia Y m�xima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float MaxWidth;

public:

	/* Array com a posi��o das salas geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gerador Salas")
		TArray<FVector> RoomsPositions;

	/* Stream de gera��o rand�mica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gerador)
		FRandomStream GeneratingStream;

	/* Array com os tipos de salas que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<TSubclassOf<ARoom>> TypesRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corredor")
		TArray<TSubclassOf<ACorridor>> CorridorTypes;

	/* N�mero m�ximo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumRooms;

	/* N�mero m�nimo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumRooms;

	/* Seed de gera��o rand�mica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Ponteiro a sala inicial. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		ARoom* StartingRoom;

	/* N�mero m�ximo de salas que podem ser geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<ARoom*> Rooms;
#pragma endregion Properties

#pragma region Constructor
	/*Constructor Padr�o. */
	ARoomGenerator();
#pragma endregion Constructor

#pragma region Functions
public:

	/*
	* Fun��o est�tica que get do gerador de salas. Fun��o utilizada por outras classes para acessar o gerador de salas.
	* @param WordlContextObject - Contexto de gera��o da sala.
	* @return Ponteiro ao gerador de salas.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ARoomGenerator* GetRoomGenerator(UObject* WorldContextObject);

	/*
	* Fun��o de inicializa��o do gerador de salas, iniciando o processo de gera��o do level.
	* @param Inicial - Ponteiro a sala inicial.
	* @param Seed - Novo seed do gerador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void InitializeGenerator(ARoom* startRoom, int32 newSeed, int32 curLevel);

	/*
	* Fun��o de get da rota��o relativa de uma determinada porta com rela��o a sala e a dire��o da porta.
	* @param DirecaoSala - Rota��o da sala.
	* @param Porta - Dire��o padr�o da sala.
	* @return Rota��o da porta com rela��o a sala.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		FRotator GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door);

	/*
	* Fun��o de get do n�mero total de portas vazias dentro do array de salas.
	* @return O n�mero de salas vazias.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 GetNumVoidDoors();

	/*
	* Fun��o que retorna o �ndice da �ltima sala v�lida dentro do array de salas.
	* @return O n�mero do �ndice.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 LastValidRoom();

	/*
	* Fun��o que gera o transforma da sala a ser gerada.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que est� gerando a sala.
	* @return O transforma da sala a ser gerada.
	*/
	UFUNCTION()
		FTransform GenerateRoomTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Fun��o que gera o transforma do corredor a ser gerado.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que est� gerando a sala.
	* @return O transforma do correodr a ser gerada.
	*/
	UFUNCTION()
		FTransform GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Fun��o que seleciona a sala a ser gerada, esta fun��o checa quais salas podem ser geradas e garante que salas especiais ser�o geradas.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @return Classe da sala a ser gerada.
	*/
	UFUNCTION()
		TSubclassOf<ARoom> SelectRoom(ARoom* previousRoom);

	/*
	* Fun��o que utiliza o seed para o set do n�mero de salas a serem geradas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SetNumRooms(int32 currentLevel);

	/*
	* Fun��o que adiciona uma nova sala ao array de salas.
	* @param sala - Ponteiro a sala a ser adicionada
	*/
	UFUNCTION()
		void AddToDoorArray(ARoom* room);

	/*
	* Fun��o que gera o level com todas as salas, corredores e faz o spawn dos inimigos.
	* Esta fun��o � utilizada recursivamente.
	* @param SalaAtual - Ponteiro a sala atual da gera��o.
	*/
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Gerador Salas")
		void GenerateLevel(ARoom* currentRoom);

	/*
	* Fun��o que gera uma sala.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que vai gerar a sala.
	* @return Ponteiro a sala gerada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		ARoom* GenerateRoom (ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Fun��o que gera um corredor.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rota��o da porta que vai gerar o corredor.
	*/
	UFUNCTION()
		void GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Fun��o que impede a colis�o de uma nova sala com salas que j� foram geradas e com os limites de gera��o.
	* @param Trans - transform da sala a ser gerada para checar a colis�o.
	* @param DirecaoPorta - Rota��o da porta que vai gerar a sala.
	*/
	UFUNCTION()
		void CheckColision(const FTransform& trans, const FRotator doorDirection);

	/*
	* Fun��o que gera uma sala especial.
	*/
	UFUNCTION()
		void GenerateSpecialRoom();

	/*
	* Fun��o que checa se uma posi��o est� dentro do array de posi��es, esta fun��o � usada para impedir colis�es.
	* @param pos - Vetor da posi��o a ser testada.
	* @return true quando o vetor est� no array de posi��es
	*/
	UFUNCTION()
		bool InPositionArray(const FVector& pos);

	/*
	* Fun��o que checa se um transform colide com uma sala numa determinada dire��o
	* @param Trans - Transform a ser testado.
	* @param Direcao -	Direcao da porta que gerou o transform.
	* @return true quando o transform colide.
	*/
	UFUNCTION()
		bool IsCollidingToDirection(EDoorDirection direction, const FTransform& trans);

	/*
	* Evento que � disparado quando a gera��o foi terminada.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Sala")
		void OnLevelGenerated();

	/*
	* Fun��o que carregar de um save game as salas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void LoadRooms();

	/*
	* Fun��o que salva as salas em um save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SaveRooms();
#pragma endregion Functions

};
