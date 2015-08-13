// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sala.generated.h"

UENUM(BlueprintType)
enum class EDificuldadeSala : uint8
{
	FACIL,
	NORMAL,
	DIFICIL

};

UENUM(BlueprintType)
enum class ENumeroPortas : uint8
{
	ZERO,
	UMA,
	DUAS,
	TRES,
	QUATRO,
};

UENUM(BlueprintType)
enum class EDirecaoPorta : uint8
{
	OESTE,
	NORTE,
	LESTE,
	SUL,

};

UENUM(BlueprintType)
enum class EFormatoSala : uint8
{
	PADRAO,
	ESQUERDA,
	DIREITA

};

UENUM(BlueprintType)
enum class ETipoSala : uint8
{
	NORMAL,
	INICIO,
	ITEM,
	CHAVE,
	BOSS

};

UCLASS()
class PROJETOROGUE_API ASala : public AActor
{
	GENERATED_BODY()
protected:

	//SALA

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EFormatoSala DirecaoSala;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		ETipoSala TipoSala;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		EDificuldadeSala Dificuldade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		FVector EscalaPadrao;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sala")
		float OffsetSala;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
	//	UBoxComponent* TriggerInimigos;

	//PORTAS

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Portas")
		ENumeroPortas NumeroPortas;

	UPROPERTY(BlueprintReadWrite, Category = "Portas")
		TArray<class APorta*> Portas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portas")
		TArray < TEnumAsByte<EDirecaoPorta> > DirecaoPortas;


	//INIMIGOS

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inimigos")
		TArray<class AInimigo*> Inimigos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosFacil;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosNormal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inimigos")
		TArray<TSubclassOf<AInimigo>> InimigosDificil;

	//ITENS

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Itens")
		TArray<TSubclassOf<class UItem>> PossiveisItens;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inimigos")
		bool bSalaTemInimigos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sala")
		TArray<ASala*> SalasConectadas;

	UPROPERTY()
		bool bVisitada;

	UFUNCTION()
		FVector GetEscala();

	UFUNCTION()
		int32 GetOffset();

	UFUNCTION()
		ENumeroPortas GetNumPortas();

	UFUNCTION()
		EFormatoSala GetDirecao();

	UFUNCTION()
		ETipoSala GetTipo();

	UFUNCTION()
		TArray<TEnumAsByte<EDirecaoPorta>> GetArrayPortas();

	UFUNCTION()
		void RemoverInimigo(AInimigo* inimigo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Spawn Inimigos", Keywords = "Spawn Inimigos"), Category = "Spawn")
		void SpawnInimigos(int32 Seed);
		virtual void SpawnInimigos_Implementation(int32 Seed);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Tipo Inimigos", Keywords = "Get Tipo Inimigos"), Category = "Inimigo")
		TSubclassOf<AInimigo> GetTipoInimigo(const TArray < TSubclassOf<AInimigo>>& InimigoDificuldade, int32 Seed);

	UFUNCTION()
		void InimigosForamDerrotados();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trancar Portas", Keywords = "Trancar Portas"), Category = "Sala")
		void TrancarPortas();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Destrancar Portas", Keywords = "Destrancar Portas"), Category = "Sala")
		virtual void DestrancarPortas();


	// Sets default values for this actor's properties
	ASala(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

};
