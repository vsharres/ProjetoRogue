// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Projectil.generated.h"

/* Estrutura que representa os stats do proj�til. */
USTRUCT()
struct FProjetilStats
{
	GENERATED_USTRUCT_BODY()
public:

	/* Intensidade da velocidade do proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Velocidade;
	/* Dano a ser causado pelo proj�til. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projetil Struct")
		float Dano;

	/* Construtor padr�o. */
	FProjetilStats(float velocidade = 200.0f, float dano = 1.0f)
	{
		Velocidade = velocidade;
		Dano = dano;
	}

	/* Overload do operador para somar os stats do jogador aos stats do proj�til.  */
	FORCEINLINE FProjetilStats& operator=(const FJogadorStats& statsJogador)
	{
		this->Velocidade = statsJogador.VelProjetil;
		this->Dano = statsJogador.Dano;

		return *this;
	}

	/* Overload do operador para somar os stats do inimigo aos stats do proj�til.  */
	FORCEINLINE FProjetilStats& operator=(const FInimigoStats& statsInimigo)
	{
		this->Velocidade = statsInimigo.VelProjetil;
		this->Dano = statsInimigo.Dano;

		return *this;
	}


};

/* Estrutura que presenta os efeitos de impacto causados pelo proj�il. */
USTRUCT()
struct FProjetilImpactoEfeito
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistem de part�culas gerado no impacto. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* Efeito;

	/* Som gerado no impacto. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* SomImpacto;

	/* Material do decal gerado durante o impacto.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UMaterial* DecalMaterial;

	/* Tamanho do decal a ser gerado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalTamanho;

	/* Tempo de vida do decal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecalVida;

	/* Construtor padr�o. */
	FProjetilImpactoEfeito()
	{
		Efeito = NULL;
		SomImpacto = NULL;
		DecalMaterial = NULL;
		DecalTamanho = 2.0f;
		DecalVida = 3.0f;
	}
};

/* Estrutura que representa os efeitos gerados quando o proj�til � atirado. */
USTRUCT()
struct FProjetilAtirarEfeitos
{
	GENERATED_USTRUCT_BODY()
public:

	/* Sistema de part�culas gerado quando o proj�til � atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* TiroFlash;

	/* Som gerado quando o proj�til � atirado. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* SomTiro;

	/* Construtor padr�o.*/
	FProjetilAtirarEfeitos()
	{
		TiroFlash = NULL;
		SomTiro = NULL;
	}
};

/*
*	Classe derivada da classe AActor.
*	Classe que represeta o proj�til atirado pelo jogador e pelos inimigos.
*/
UCLASS(ABSTRACT, Blueprintable)
class PROJETOROGUE_API AProjectil : public AActor
{
	GENERATED_BODY()

#pragma region PROPRIEDADES

public:

	/* Booleano indicando se o proj�til est� ativo. O proj�til apenas se move, � vis�vel e causa dano quando ele estiver ativado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bAtivo;

	/* Stats do proj�til. */
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		FProjetilStats Stats;
	/* Classe da anima��o da camera que ser� realizada quando o proj�til � atirado. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Efeitos")
		TSubclassOf<UCameraShake> FireCameraShake;

protected:

	/* Componente de movimenta��o do proj�til, respons�vel pelas propriedades de movimenta��o.*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UProjectileMovementComponent* CompMovimentacao;

	/* Componente de colis�o do proj�til. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		USphereComponent* CompCollisao;

	/* Componenete com o mesh do proj�til. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Projetil")
		UStaticMeshComponent* Mesh;

	/* Efeitos de impacto do proj�til. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjetilImpactoEfeito ImapctoEfeitos;

	/* Efeitos de tiro do proj�til. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Efeitos")
		FProjetilAtirarEfeitos TiroEfeitos;

#pragma endregion


#pragma region CONSTRUTOR

public:
	/* Construtor padr�o. */
	AProjectil(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region FUN��ES

	/*
	* Fun��o de get do mesh do proj�tl.
	* @return - Ponteiro ao mesh do proj�til.
	*/
	UFUNCTION(BlueprintPure, Category = "Component")
		UStaticMeshComponent* GetProjetilMesh();

	/*
	* Fun��o de get do componente de movimenta��o do proj�til.
	* @return - Ponteiro ao componente de movimenta��o.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mov Proj", Keywords = "Get Mov Proj"), Category = "Particula")
		UProjectileMovementComponent* GetMovProjetil();

	/*
	* Fun��o para inicializar o proj�til.
	* @param Inicializador - Ponteiro ao APawn respons�vel pela inicializa��o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InicializarProj", Keywords = "Inicializar Projetil"), Category = "Projetil")
		void InicializarProjetil(ACharacter* Inicializador);

	/*
	* Fun��o para ativar um proj�til.
	* @param Localizacao - Vetor da localizao a onde o proj�til ser� inicializado(Geralmente � ponto do canhao a onde s�i o tiro).
	* @param Rotacao - Vetor de rotacao de inicializa��o do projetil (Geralmente est� apontado para a posi��o da mira)
	* @param Inicializador - Ponteiro ao APawn respons�vel pela inicializa��o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ativar Projetil", Keywords = "Ativar Projetil"), Category = "Projetil")
		void AtivarProjetil(const FVector& Location, const FRotator& Rotator, ACharacter* Inicializador); //MUDAR LOCATION PARA LOCALICAZAO e ROTATOR PARA ROTACAO

	/*
	* Fun��o para desatovar um proj�til.(Geralmente chamada quando um proj�til ativo atinge um objeto)
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Desativar Projetil", Keywords = "Desativar Projetil"), Category = "Projetil")
		void DesativarProjetil();

	/*
	* Fun��o para gerar os efeitos de impacto.
	* @param Hit - Estrutura com as propriedades do ponto de colis�o.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Impacto", Keywords = "Spawn Efeitos Impacto"), Category = "Projetil")
		void GerarEfeitosImpacto(const FHitResult& Hit);

	/*
	* Fun��o para gerar os efeitos de tiro do canh�o.
	* @param Location - Local para gerar o efeito.
	* @param Rotator - Rota��o do efeito.
	* @param Componente - Componente do ator para acoplar o efeito.
	* @param Nome -  Nome do bone do mesh a qual o efeito sera acoplado.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Efeitos Tiro", Keywords = "Spawn Efeitos Tiro"), Category = "Projetil")
		void GerarEfeitosTiro(const FVector& Location, const FRotator& Rotator, USceneComponent* Componente, FName Nome);

	/* Override da fun��o de inicializa��o do ator. */
	virtual void BeginPlay() override;

	/* Override do Tick do proj�til. */
	virtual void Tick(float DeltaSeconds) override;

	/*
	* Override do Tick da sala.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Particula")
		void Atingiu();

	/*
	* Delegate de hit do projetil.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Hit", Keywords = "On Hit"), Category = "Particula")
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnHit_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion



};
