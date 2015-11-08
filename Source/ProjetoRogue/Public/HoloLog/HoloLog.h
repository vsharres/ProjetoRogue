// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HoloLog.generated.h"

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FHoloLogTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FHoloLogTable()
		: LogTexto(TEXT(""))
	{}

	/** XP to get to the given level from the previous level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoloLogText)
		FString LogTexto;

};

UCLASS()
class PROJETOROGUE_API AHoloLog : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = HoloLog)
		FText TextoLog;

	UPROPERTY(BlueprintReadWrite, Category = HoloLog)
		FDataTableRowHandle HoloLogTableHandle;

	/* Seed de geração do item. Este seed é o mesmo utilizado pelo gerador de salas. */
	UPROPERTY(BlueprintReadWrite, Category = "Seed")
		int32 Seed;
	

	// Sets default values for this actor's properties
	AHoloLog();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
