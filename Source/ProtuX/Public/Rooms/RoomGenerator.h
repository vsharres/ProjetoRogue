// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.h"
#include "RoomGenerator.generated.h"

/*
*	Class inherited from ARoom.
*	Class that represents the room generator. This class is responsible for the whole level generation.
*/
UCLASS()
class PROTUX_API ARoomGenerator : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:

	/* Number of rooms to be generated. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		int32 NumGeneratedRooms;

	/* Index where rooms with 2 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Rooms")
		int32 Room2DIndex;

	/* Index where rooms with 3 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Rooms")
		int32 Room3DIndex;

	/* Index where rooms with 4 doors starts in the room array. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "3"), Category = "Rooms")
		int32 Room4DIndex;

	/* Item room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<class ARoom> ItemRoom;

	/* Key room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ARoom> KeyRoom;

	/* Boss room class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ARoom> BossRoom;

	/* Corridor shop class. */
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
		TSubclassOf<ACorridor> ShopCorridor;

	/* Boolean indicating if the shop corridor was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Corridor")
		bool bIsShopSpawned;

	/* Boolean indicating if the item room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bIsItemSpawned;

	/* Boolean indicating if the key room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bIsKeySpawned;

	/* Boolean indicating if the boss room was spawned. */
	UPROPERTY(VisibleAnywhere, Category = "Rooms")
		bool bBossSpawned;

	/* Current generated room. */
	UPROPERTY()
		TSubclassOf<ARoom> GeneratedRoom;

	/* Array with the last generated room. */
	UPROPERTY()
		TArray<TSubclassOf<ARoom>> PreviousGeneratedRooms;

	/* Array to be used during loading of the level. */
	UPROPERTY()
		TArray<bool> LoadedRooms;

	/* Max Length of the level. Which is the maximum distance a room can be from the starting room. */
	UPROPERTY(EditDefaultsOnly, Category = "Generator")
		float MaxLength;

	/* Max Width of the level. Which is the maximum distance a room can be from the starting room. */
	UPROPERTY(EditDefaultsOnly, Category = "Generator")
		float MaxWidth;

public:

	/* Array with the rooms positions. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator Rooms")
		TArray<FVector> RoomsPositions;

	/* Generator Random stream. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		FRandomStream GeneratingStream;

	/* Array with the types of rooms that can be spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
		TArray<TSubclassOf<ARoom>> TypesRooms;

	/* Array with the types of corridors that can be spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corridor")
		TArray<TSubclassOf<ACorridor>> CorridorTypes;

	/* Maximus number of rooms to be generated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumRooms;

	/* Minimum number of rooms to be generated.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumRooms;

	/* Random seed number. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Starting room pointer. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
		ARoom* StartingRoom;

	/* Array of rooms in the level. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rooms")
		TArray<ARoom*> Rooms;

#pragma endregion Properties

#pragma region Constructor

	/*Standard Constructor.*/
	ARoomGenerator();

#pragma endregion Constructor

#pragma region Functions

public:

	/*
	* Função estática que get do Generator de Rooms. Função utilizada por outras classes para acessar o Generator de Rooms.
	* @param WordlContextObject - Contexto de geração da sala.
	* @return Ponteiro ao Generator de Rooms.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ARoomGenerator* GetRoomGenerator(UObject* WorldContextObject);

	/*
	* Função de inicialização do Generator de Rooms, iniciando o processo de geração do level.
	* @param Inicial - Ponteiro a sala inicial.
	* @param Seed - Novo seed do Generator.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void InitializeGenerator(ARoom* startRoom, int32 newSeed, int32 curLevel);

	/*
	* Função de get da rotação relativa de uma determinada porta com relação a sala e a direção da porta.
	* @param DirecaoSala - Rotação da sala.
	* @param Porta - Direção padrão da sala.
	* @return Rotação da porta com relação a sala.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		FRotator GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door);

	/*
	* Função de get do número total de portas vazias dentro do array de Rooms.
	* @return O número de Rooms vazias.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		int32 GetNumVoidDoors();

	/*
	* Função que retorna o índice da última sala válida dentro do array de Rooms.
	* @return O número do índice.
	*/
	UFUNCTION(BlueprintPure, Category = "Generator Rooms")
		int32 LastValidRoom();

	/*
	* Função que gera o transforma da sala a ser gerada.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que está gerando a sala.
	* @return O transforma da sala a ser gerada.
	*/
	UFUNCTION()
		FTransform GenerateRoomTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Função que gera o transforma do Corridor a ser gerado.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que está gerando a sala.
	* @return O transforma do correodr a ser gerada.
	*/
	UFUNCTION()
		FTransform GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Função que seleciona a sala a ser gerada, esta função checa quais Rooms podem ser geradas e garante que Rooms especiais serão geradas.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @return Classe da sala a ser gerada.
	*/
	UFUNCTION()
		TSubclassOf<ARoom> SelectRoom(ARoom* previousRoom);

	/*
	* Função que utiliza o seed para o set do número de Rooms a serem geradas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void SetNumRooms(int32 currentLevel);

	/*
	* Função que adiciona uma nova sala ao array de Rooms.
	* @param sala - Ponteiro a sala a ser adicionada
	*/
	UFUNCTION()
		void AddToDoorArray(ARoom* room);

	/*
	* Função que gera o level com todas as Rooms, Corridores e faz o spawn dos inimigos.
	* Esta função é utilizada recursivamente.
	* @param SalaAtual - Ponteiro a sala atual da geração.
	*/
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Generator Rooms")
		void GenerateLevel(ARoom* currentRoom);

	/*
	* Função que gera uma sala.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar a sala.
	* @return Ponteiro a sala gerada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		ARoom* GenerateRoom (ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Função que gera um Corridor.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar o Corridor.
	*/
	UFUNCTION()
		void GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Função que impede a colisão de uma nova sala com Rooms que já foram geradas e com os limites de geração.
	* @param Trans - transform da sala a ser gerada para checar a colisão.
	* @param DirecaoPorta - Rotação da porta que vai gerar a sala.
	*/
	UFUNCTION()
		void CheckColision(const FTransform& trans, const FRotator doorDirection);

	/*
	* Função que gera uma sala especial.
	*/
	UFUNCTION()
		void GenerateSpecialRoom();

	/*
	* Função que checa se uma posição está dentro do array de posições, esta função é usada para impedir colisões.
	* @param pos - Vetor da posição a ser testada.
	* @return true quando o vetor está no array de posições
	*/
	UFUNCTION()
		bool InPositionArray(const FVector& pos);

	/*
	* Função que checa se um transform colide com uma sala numa determinada direção
	* @param Trans - Transform a ser testado.
	* @param Direcao -	Direcao da porta que gerou o transform.
	* @return true quando o transform colide.
	*/
	UFUNCTION()
		bool IsCollidingToDirection(EDoorDirection direction, const FTransform& trans);

	/*
	* Evento que é disparado quando a geração foi terminada.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Room")
		void OnLevelGenerated();

	/*
	* Função que carregar de um save game as Rooms.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void LoadRooms();

	/*
	* Função que salva as Rooms em um save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Generator Rooms")
		void SaveRooms();
#pragma endregion Functions

};
