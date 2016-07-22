// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"


/* Classe que representa uma das portas das salas. */
UCLASS()
class PROTUX_API ADoor : public AActor
{
	GENERATED_BODY()
	
#pragma region Properties

public:	

	/* Booleando que indica se a porta deve ser aberta. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bOpenDoor;

	/* Booleando que indica se a porta deve ser aberta. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bCloseDoor;

	/* Booleando que indica se a porta deve ser trancada. */
	UPROPERTY(BlueprintReadWrite, Category = "Porta")
		bool bIsDoorLocked;

	/* Ponteiro a sala que a porta pertence. */
	UPROPERTY(BlueprintReadWrite, Category = "Sala")
	class ARoom* ParentRoom;

#pragma endregion Properties

#pragma region Functions

public:

	/*
	* Evento disparado para trancar a porta.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Trancar Porta", Keywords = "Trancar Porta"), Category = "Porta")
		void LockDoor();

	/*
	* Evento disparado para destrancar a porta.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Porta", Keywords = "Destrancar Porta"), Category = "Porta")
		void UnlockDoor();


	// Constructor
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
#pragma endregion Functions
	
};
