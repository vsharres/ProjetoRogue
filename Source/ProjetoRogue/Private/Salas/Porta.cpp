// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "Porta.h"


// Sets default values
APorta::APorta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAbrirPorta = false;
	bFecharPorta = false;
	bPortaTrancada = false;

}

// Called when the game starts or when spawned
void APorta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APorta::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

