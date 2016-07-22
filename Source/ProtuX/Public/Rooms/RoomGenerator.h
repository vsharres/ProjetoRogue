// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.h"
#include "RoomGenerator.generated.h"

/*
*	Classe que representa o gerador de salas. O gerador é responsável por gerar o level, gerar a navigação e fazer o spawn dos inimigos.
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

	/* Index onde começam as salas com duas portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1"), Category = "Salas")
		int32 Room2DIndex;

	/* Index onde começam as salas com três portas no array de salas. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "2"), Category = "Salas")
		int32 Room3DIndex;

	/* Index onde começam as salas com quatro portas no array de salas. */
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

	/* Booleano que indica se o corredor com a loja já foi gerado. */
	UPROPERTY(VisibleAnywhere, Category = "Corredor")
		bool bIsShopSpawned;

	/* Booleano que indica se a sala do item já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bIsItemSpawned;

	/* Booleano que indica se a sala da chave já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bIsKeySpawned;

	/* Booleano que indica se a sala do boss já foi gerada. */
	UPROPERTY(VisibleAnywhere, Category = "Salas")
		bool bBossSpawned;

	/* Sala que está sendo gerada atualmente. */
	UPROPERTY()
		TSubclassOf<ARoom> GeneratedRoom;

	/* Array com as últimas salas geradas. */
	UPROPERTY()
		TArray<TSubclassOf<ARoom>> PreviousGeneratedRooms;

	/* Array para verificar se todas as salas foram carregadas de um save game. */
	UPROPERTY()
		TArray<bool> LoadedRooms;

	/* Distância X máxima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float MaxLength;

	/* Distância Y máxima que uma sala pode estar da sala inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Gerador")
		float MaxWidth;

public:

	/* Array com a posição das salas geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gerador Salas")
		TArray<FVector> RoomsPositions;

	/* Stream de geração randômica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gerador)
		FRandomStream GeneratingStream;

	/* Array com os tipos de salas que podem ser gerados. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<TSubclassOf<ARoom>> TypesRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corredor")
		TArray<TSubclassOf<ACorridor>> CorridorTypes;

	/* Número máximo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MaxNumRooms;

	/* Número mínimo de salas que podem ser geradas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas", meta = (UIMin = "5", UIMax = "15"))
		int32 MinNumRooms;

	/* Seed de geração randômica. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int32 Seed;

	/* Ponteiro a sala inicial. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salas")
		ARoom* StartingRoom;

	/* Número máximo de salas que podem ser geradas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Salas")
		TArray<ARoom*> Rooms;
#pragma endregion Properties

#pragma region Constructor
	/*Constructor Padrão. */
	ARoomGenerator();
#pragma endregion Constructor

#pragma region Functions
public:

	/*
	* Função estática que get do gerador de salas. Função utilizada por outras classes para acessar o gerador de salas.
	* @param WordlContextObject - Contexto de geração da sala.
	* @return Ponteiro ao gerador de salas.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		static ARoomGenerator* GetRoomGenerator(UObject* WorldContextObject);

	/*
	* Função de inicialização do gerador de salas, iniciando o processo de geração do level.
	* @param Inicial - Ponteiro a sala inicial.
	* @param Seed - Novo seed do gerador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void InitializeGenerator(ARoom* startRoom, int32 newSeed, int32 curLevel);

	/*
	* Função de get da rotação relativa de uma determinada porta com relação a sala e a direção da porta.
	* @param DirecaoSala - Rotação da sala.
	* @param Porta - Direção padrão da sala.
	* @return Rotação da porta com relação a sala.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		FRotator GetRelativeDoorDirection(const FRotator roomDirection, const EDoorDirection& door);

	/*
	* Função de get do número total de portas vazias dentro do array de salas.
	* @return O número de salas vazias.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
		int32 GetNumVoidDoors();

	/*
	* Função que retorna o índice da última sala válida dentro do array de salas.
	* @return O número do índice.
	*/
	UFUNCTION(BlueprintPure, Category = "Gerador Salas")
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
	* Função que gera o transforma do corredor a ser gerado.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que está gerando a sala.
	* @return O transforma do correodr a ser gerada.
	*/
	UFUNCTION()
		FTransform GenerateCorridorTrans(ARoom* previousRoom, const FRotator doorDirection);

	/*
	* Função que seleciona a sala a ser gerada, esta função checa quais salas podem ser geradas e garante que salas especiais serão geradas.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @return Classe da sala a ser gerada.
	*/
	UFUNCTION()
		TSubclassOf<ARoom> SelectRoom(ARoom* previousRoom);

	/*
	* Função que utiliza o seed para o set do número de salas a serem geradas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SetNumRooms(int32 currentLevel);

	/*
	* Função que adiciona uma nova sala ao array de salas.
	* @param sala - Ponteiro a sala a ser adicionada
	*/
	UFUNCTION()
		void AddToDoorArray(ARoom* room);

	/*
	* Função que gera o level com todas as salas, corredores e faz o spawn dos inimigos.
	* Esta função é utilizada recursivamente.
	* @param SalaAtual - Ponteiro a sala atual da geração.
	*/
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Gerador Salas")
		void GenerateLevel(ARoom* currentRoom);

	/*
	* Função que gera uma sala.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar a sala.
	* @return Ponteiro a sala gerada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		ARoom* GenerateRoom (ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Função que gera um corredor.
	* @param SalaAnterior - Ponteiro a sala anterior.
	* @param DirecaoPorta - Rotação da porta que vai gerar o corredor.
	*/
	UFUNCTION()
		void GenerateCorridor(ARoom* previousRoom, const FRotator& doorDirection);

	/*
	* Função que impede a colisão de uma nova sala com salas que já foram geradas e com os limites de geração.
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
	UFUNCTION(BlueprintImplementableEvent, Category = "Sala")
		void OnLevelGenerated();

	/*
	* Função que carregar de um save game as salas.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void LoadRooms();

	/*
	* Função que salva as salas em um save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gerador Salas")
		void SaveRooms();
#pragma endregion Functions

};
