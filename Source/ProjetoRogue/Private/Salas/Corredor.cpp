// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoRogue.h"
#include "Public/Salas/Corredor.h"


// Sets default values
ACorredor::ACorredor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACorredor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorredor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

