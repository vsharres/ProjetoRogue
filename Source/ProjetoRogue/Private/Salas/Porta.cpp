// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Porta.h"

APorta::APorta()
{
 	//Inicializando as propriedades.
	PrimaryActorTick.bCanEverTick = true;
	bAbrirPorta = false;
	bFecharPorta = false;
	bPortaTrancada = false;

}

// Called when the game starts or when spawned
void APorta::BeginPlay()
{
	Super::BeginPlay(); //Interface de inicialização
	
}

// Called every frame
void APorta::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime ); //Interface de tick

}

