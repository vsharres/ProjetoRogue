// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Door.h"

ADoor::ADoor()
{
 	//Inicializando as propriedades.
	PrimaryActorTick.bCanEverTick = true;
	bOpenDoor = false;
	bCloseDoor = false;
	bIsDoorLocked = false;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime ); //Interface de tick

}

