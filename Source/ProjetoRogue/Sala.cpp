// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Sala.h"


// Sets default values
ASala::ASala()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Numero_Portas = ENumeroPortas::ZERO;
	Salas_Conectadas.Empty();
	bVisited = false;

}

// Called when the game starts or when spawned
void ASala::BeginPlay()
{
	Super::BeginPlay();
	
}

