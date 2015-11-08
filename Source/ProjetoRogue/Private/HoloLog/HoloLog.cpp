// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "HoloLog.h"


// Sets default values
AHoloLog::AHoloLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoloLog::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoloLog::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

