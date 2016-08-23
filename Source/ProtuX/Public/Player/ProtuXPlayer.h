// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DamageInterface.h"
#include "Item.h"
#include "ProtuXPlayer.generated.h"

#define MAXHEALTH_MAX 500.0f
#define MAXHEALTH_MIN 50.0f
#define ENERGY_MAX 300.0f
#define ENERGY_MIN 0.0f
#define SPEED_MAX 1800.0f
#define SPEED_MIN 600.0f
#define DAMAGE_MAX 50.0f
#define DAMAGE_MIN 5.0f
#define FIRERATE_MAX 10.0f
#define FIRERATE_MIN 1.0f
#define ACCURACY_MAX 30.0f
#define ACCURACY_MIN 1.0f
#define MUZZLESPEED_MAX 7000.0f
#define MUZZLESPEED_MIN 1000.0f

/* Estrutura responsável por organizar e conter os stats do jogador. */
USTRUCT()
struct FPlayerStats
{
	GENERATED_USTRUCT_BODY()

		/* Vida atual do jogador. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Player Struct")
		float Health;

	/* Vida máxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Player Struct")
		float MaxHealth;

	/* Energia atual do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Player Struct")
		float Energy;

	/* Energia máxima do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Player Struct")
		float MaxEnergy;

	/* Velocidade de movimentação do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "600.0", ClampMax = "1800.0", UIMin = "600.0", UIMax = "1800.0"), Category = "Player Struct")
		float Speed;

	/* Dano causado pelo jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "5.0", ClampMax = "50.0", UIMin = "5.0", UIMax = "50.0"), Category = "Player Struct")
		float Damage;

	/* Frequência de tiro do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0"), Category = "Player Struct")
		float FireRate;

	/* Precisao dos tiros do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "30.0", UIMin = "1.0", UIMax = "30.0"), Category = "Player Struct")
		float Accuracy;

	/* Velocidade do projétil do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1000.0", ClampMax = "7000.0", UIMin = "1000.0", UIMax = "7000.0"), Category = "Player Struct")
		float MuzzleSpeed;

	/* Overload do operador de atribuição por soma, para facilitar mudanças nos stats. */
	FORCEINLINE FPlayerStats& operator+=(const FItemStats& itemStats)
	{
		this->MaxHealth += itemStats.AddMaxHealth;
		this->MaxEnergy += itemStats.AddMaxEnergy;
		this->Speed += itemStats.AddSpeed;
		this->FireRate += itemStats.AddFireRate;
		this->Damage += itemStats.AddDamage;
		this->Accuracy += itemStats.AddAccuracy;
		this->MuzzleSpeed += itemStats.AddMuzzleSpeed;

		AddEnergy(itemStats.AddEnergy); //Adicionar a nova energia calculada
		AddHealth(itemStats.AddHealth); //Adicionar a nova vida calculada

		ClampValues(); //garantir que os valores nao passam dos valores limites.

		return *this;
	}

	/* Overload do operador de atribuição por subtração, para facilitar mudanças nos stats. */
	FORCEINLINE FPlayerStats& operator-=(const FItemStats& itemStats)
	{
		this->MaxHealth -= itemStats.AddMaxHealth;
		this->MaxEnergy -= itemStats.AddMaxEnergy;
		this->Speed -= itemStats.AddSpeed;
		this->FireRate -= itemStats.AddFireRate;
		this->Damage -= itemStats.AddDamage;
		this->Accuracy -= itemStats.AddAccuracy;
		this->MuzzleSpeed -= itemStats.AddMuzzleSpeed;

		AddEnergy(-itemStats.AddEnergy); //remover a nova energia calculada
		AddHealth(-itemStats.AddHealth); //remover a nova vida calculada

		ClampValues(); //garantir que os valores nao passam dos valores limites.

		return *this;
	}

	/*
	* Função para realizar um clamp no valor dos stats a serem adicionar, para garantir que os limites nao serão passados, função usada quando um item é aplicado.
	* @param itemStats - Referência constante ao item a ser adicionado.
	* @return o novo stat calculado.
	*/
	FORCEINLINE FItemStats ClampAddStats(const FItemStats& itemStats)
	{
		FItemStats toReturn;

		if (itemStats.AddDamage + this->Damage > DAMAGE_MAX) //checar dano maximo
		{
			toReturn.AddDamage = DAMAGE_MAX - this->Damage;
		}
		else if (itemStats.AddDamage + this->Damage < DAMAGE_MIN) //checar dano minimo
		{
			toReturn.AddDamage = DAMAGE_MIN - this->Damage;
		}
		else
		{
			toReturn.AddDamage = itemStats.AddDamage;
		}

		if (itemStats.AddFireRate + this->FireRate > FIRERATE_MAX) //checar fire rate maximo
		{
			toReturn.AddFireRate = FIRERATE_MAX - this->FireRate;
		}
		else if (itemStats.AddFireRate + this->FireRate < FIRERATE_MIN) // checar fire rate minimo
		{
			toReturn.AddFireRate = FIRERATE_MIN - this->FireRate;
		}
		else
		{
			toReturn.AddFireRate = itemStats.AddFireRate;
		}

		if (itemStats.AddAccuracy + this->Accuracy > ACCURACY_MAX) //checar precisao maxima
		{
			toReturn.AddAccuracy = ACCURACY_MAX - this->Accuracy;
		}
		else if (itemStats.AddAccuracy + this->Accuracy < ACCURACY_MIN) //checar precisao minima
		{
			toReturn.AddAccuracy = ACCURACY_MIN - this->Accuracy;
		}
		else
		{
			toReturn.AddAccuracy = itemStats.AddAccuracy;
		}

		if (itemStats.AddSpeed + this->Speed > SPEED_MAX) //checar velocidade de movimentação maxima
		{
			toReturn.AddHealth = SPEED_MAX - this->Speed;
		}
		else if (itemStats.AddSpeed + this->Speed < SPEED_MIN) //checar velocidade de movimentação minima
		{
			toReturn.AddSpeed = SPEED_MIN - this->Speed;
		}
		else
		{
			toReturn.AddSpeed = itemStats.AddSpeed;
		}

		if (itemStats.AddMuzzleSpeed + this->MuzzleSpeed > MUZZLESPEED_MAX) //checar velocidade do projetil maxima
		{
			toReturn.AddMuzzleSpeed = MUZZLESPEED_MAX - this->MuzzleSpeed;
		}
		else if (itemStats.AddMuzzleSpeed + this->MuzzleSpeed < MUZZLESPEED_MIN) //checar velocidade do projetil minima
		{
			toReturn.AddMuzzleSpeed = MUZZLESPEED_MIN - this->MuzzleSpeed;
		}
		else
		{
			toReturn.AddMuzzleSpeed = itemStats.AddMuzzleSpeed;
		}

		if (itemStats.AddMaxHealth + this->MaxHealth > MAXHEALTH_MAX) //checar vida maxima
		{
			toReturn.AddMaxHealth = MAXHEALTH_MAX - this->MaxHealth;
		}
		else if (itemStats.AddMaxHealth + this->MaxHealth < MAXHEALTH_MIN) // checar vida minima
		{
			toReturn.AddMaxHealth = MAXHEALTH_MIN - this->MaxHealth;
		}
		else
		{
			toReturn.AddMaxHealth = itemStats.AddMaxHealth;
		}

		if (itemStats.AddHealth + this->Health > MaxHealth) // checar vida atual
		{
			toReturn.AddHealth = MaxHealth - this->Health;
		}
		else if (itemStats.AddHealth + this->Health < MAXHEALTH_MIN)
		{
			toReturn.AddHealth = MAXHEALTH_MIN - this->Health;
		}
		else
		{
			toReturn.AddHealth = itemStats.AddHealth;
		}

		if (itemStats.AddMaxEnergy + this->MaxEnergy > ENERGY_MAX) //checar energia maxima
		{
			toReturn.AddMaxEnergy = ENERGY_MAX - this->MaxEnergy;
		}
		else if (itemStats.AddMaxEnergy + this->MaxEnergy < ENERGY_MIN) //checar energia minima
		{
			toReturn.AddMaxEnergy = ENERGY_MIN - this->MaxEnergy;
		}
		else
		{
			toReturn.AddMaxEnergy = itemStats.AddMaxEnergy;
		}

		if (itemStats.AddEnergy + this->Energy > MaxEnergy) // checar energia
		{
			toReturn.AddEnergy = MaxEnergy - this->Energy;
		}
		else if (itemStats.AddEnergy + this->Energy < ENERGY_MIN)
		{
			toReturn.AddEnergy = ENERGY_MIN - this->Energy;
		}
		else
		{
			toReturn.AddEnergy = itemStats.AddEnergy;
		}

		return toReturn;
	}

	/*
	* Função  para garantir que os limites dos stats nao serão passados
	*/
	FORCEINLINE void ClampValues()
	{
		if (MaxHealth > MAXHEALTH_MAX)
		{
			MaxHealth = MAXHEALTH_MAX;
		}
		else if (MaxHealth < MAXHEALTH_MIN)
		{
			MaxHealth = MAXHEALTH_MIN;
		}

		if (Speed > SPEED_MAX)
		{
			Speed = SPEED_MAX;
		}
		else if (Speed < SPEED_MIN)
		{
			Speed = SPEED_MIN;
		}

		if (FireRate > FIRERATE_MAX)
		{
			FireRate = FIRERATE_MAX;
		}
		else if (FireRate < FIRERATE_MIN)
		{
			FireRate = FIRERATE_MIN;
		}

		if (Damage > DAMAGE_MAX)
		{
			Damage = DAMAGE_MAX;
		}
		else if (Damage < DAMAGE_MIN)
		{
			Damage = DAMAGE_MIN;
		}

		if (Accuracy > ACCURACY_MAX)
		{
			Accuracy = ACCURACY_MAX;
		}
		else if (Accuracy < ACCURACY_MIN)
		{
			Accuracy = ACCURACY_MIN;
		}

		if (MuzzleSpeed > MUZZLESPEED_MAX)
		{
			MuzzleSpeed = MUZZLESPEED_MAX;
		}
		else if (MuzzleSpeed < MUZZLESPEED_MIN)
		{
			MuzzleSpeed = MUZZLESPEED_MIN;
		}

		if (MaxEnergy > ENERGY_MAX)
		{
			MaxEnergy = ENERGY_MAX;
		}
		else if (MaxEnergy < ENERGY_MIN)
		{
			MaxEnergy = ENERGY_MIN;
		}

	}

	/*
	* Função para adicionar vida aos stats.
	* @param vidaAdicionada - float com a vida a ser adicionada
	*/
	FORCEINLINE void AddHealth(float healthAdd)
	{
		Health += healthAdd;

		if (Health > MaxHealth) //checar limites
		{
			Health = MaxHealth;
		}
		else if (Health < 0)
		{
			Health = 0;
		}

	}

	/*
	* Função para adicionar energia aos stats.
	* @param energidaAdicionada - float com a energia a ser adicionada
	*/
	FORCEINLINE void AddEnergy(float energyAdded)
	{
		Energy += energyAdded;

		if (Energy > MaxEnergy) //checar limites
		{
			Energy = MaxEnergy;
		}
		else if (Energy < 0)
		{
			Energy = 0;
		}
	}

	/*
	* Função para setar novos stats.
	* @param stats - referência constante aos stats a serem setados.
	*/
	FORCEINLINE void SetStats(const FPlayerStats& stats)
	{
		this->Health = stats.Health;
		this->MaxHealth = stats.MaxHealth;
		this->Energy = stats.Energy;
		this->MaxEnergy = stats.MaxEnergy;
		this->Speed = stats.Speed;
		this->Damage = stats.Damage;
		this->FireRate = stats.FireRate;
		this->Accuracy = stats.Accuracy;
		this->MuzzleSpeed = stats.MuzzleSpeed;

		ClampValues(); //checar os valores para não passar dos limites
	}

	//Constructor padrão
	FPlayerStats(float healthMax = 100.0f, float speed = 600.0f, float fireRate = 0.05f, float damage = 5.0f, float accuracy = 5.0f, float muzzleSpeed = 1500.0f, float energy = 100)
	{
		MaxHealth = healthMax;
		Speed = speed;
		FireRate = fireRate;
		Damage = damage;
		Accuracy = accuracy;
		MuzzleSpeed = muzzleSpeed;
		Energy = energy;
		MaxEnergy = Energy;
		Health = MaxHealth;

		ClampValues(); //checar os valores para não passar dos limites
	}

	//Constructor por copia.
	FPlayerStats(const FPlayerStats& other)
	{
		MaxHealth = other.MaxHealth;
		Speed = other.Speed;
		FireRate = other.FireRate;
		Damage = other.Damage;
		Accuracy = other.Accuracy;
		MuzzleSpeed = other.MuzzleSpeed;
		Energy = other.Energy;
		MaxEnergy = other.MaxEnergy;
		Health = other.Health;

		ClampValues(); //checar os valores para não passar dos limites
	}

};

/* Enumeração que os tipos de interação que o jogador pode fazer */
UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	NONE,
	KEY,
	ITEM,
	SHOP,
	ELEVATOR,
	HOLOLOG,
	TUTORIALPROMP
};

/* Enumeração com o tipo do promp de tutorial. */
UENUM(BlueprintType)
enum class ETutorialPromp :uint8
{
	BOSSDOOR,
	KEY,
	SHOP,
	PASSIVEITEM,
	ACTIVEITEM,
	INVENTORY
};

/* Enumeração com o estado de inicialização do jogador atual. */
UENUM(BlueprintType)
enum class EInitializationState :uint8
{
	BOOTUP,
	NEWLEVEL,
	PLAY,
};

/*
* Classe derivada da classe ACharacter
* Classe responsável por toda a funcionalidade do jogador.
*/
UCLASS()
class PROTUX_API AProtuXPlayer : public ACharacter, public IDamageInterface //Interface de dano
{
	GENERATED_BODY()


public:
	/* Nome do protótipo atual. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nome")
		FString Name;

	/* Stats do jogador. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FPlayerStats Stats;

	/* Scrap total do jogador */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moedas")
		int32 Coins;

	//ITENS
	/* Cooldown atual do item ativo. */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		float CurCooldown;

	/* Duração do cooldown do item ativo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "5.0"), Category = "Item")
		float CooldownTime;

	/* Velocidade com que o cooldown é alterado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1", UIMax = "10.0"), Category = "Item")
		float CooldDownRate;

	/* Booleando indiciando se o jogador possui a chave. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bHasKey;

	/* Array com os itens passivos que o jogador possui. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<class UPassiveItem*> PassiveItems;

	/* Booleano indicando se o jogador já encontrou o item da fase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bFoundItem;

	//PROJETIL

	/* Número de projéteis dentro do pool de projéteis. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
		int32 NumProjectiles;

	/* Classe do tipo de projétil inicial. */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class UProjectileItem> StartingProjectil;

	/* Classe do projétil encontrado. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<UProjectileItem> FoundProjectil;

	/* Prójétil sendo utilizado no momento. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UProjectileItem* CurrentProjectil;

	/* Array com todos os projéteis que podem ser disparado. Esse pool é estático, isto é, todos os projéteis são alocados inicialmente.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TArray<AProjectile*> ProjectilePool;

	/* Nome do socket no canhao da onde os projéteis são atirados. */
	UPROPERTY()
		FName ProjectileSocket;

	/* Cor atual dos projéteis. */
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
		FLinearColor ProjectileColor;

	/* Constructor Padrão. */
	AProtuXPlayer(const FObjectInitializer& ObjectInitializer);

	/*
	* Função de inicialização do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void InitializePlayer();

	/*
	* Função para gerar o nome da versão do protótipo do jogador.
	* @param index - Índice da versão do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nome")
		void GenerateName(int32 index);

	/*
	* Função para atulizar as propriedades de movimentação com os stats atuais do jogador.
	*/
	UFUNCTION()
		void UpdateProjectileStats();

	/*
	* Função para inicializar um projétil dentro do pool de projéteis.
	* @param bDesativar - Argumento opicional para desativar os projéteis.
	*/
	UFUNCTION()
		void InitializeProjectile(bool bIsDeactivated = false);

	/*
	* Função para gerar o pool de projéteis.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void GenerateProjectilePool();

	/*
	* Função para checar se o jogador ainda está vivo.
	* @return verdadeiro se o jogador está vivo.
	*/
	UFUNCTION(BlueprintPure, Category = Player)
		bool IsAlive();

	/*
	* Função para adicionar vida ao jogador.
	* @param vida - float com a vida a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddHelath(float health);
	/*
	* Função para adicionar energia ao jogador.
	* @param energia - float com a energia a ser adicionada.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddEnergy(float energy);

	/*
	* Função para adicionar scrap ao jogador.
	* @param valor - inteiro com o número de scrap a ser adicionado.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddCoins(int32 value);

	/*
	* Função para salvar as propriedades do jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void SavePlayerState();

	/*
	* Função para carregar o jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void LoadPlayerState();

	/*
	* Função para criar as propriedades de um novo jogador.
	*/
	UFUNCTION(BlueprintCallable, Category = "Jogo")
		void NewPlayer();

	/*
	* Função para usar o item ativo.
	* @param bDesativar - argumento opicional para desativar um item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		void UseItem(bool bIsDeactivated = false);

	/*
	* Evento para atualizar o mesh do canhão.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void UpdateMesh();

	//INTERFACES

	/* Override do tick do jogador. */
	virtual void Tick(float DeltaSeconds) override;

	/* Overload do evento de EndPlay do jogador. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	* Interface para o jogador receber dano.
	* @param dano - Referência constante ao dano a ser tomado.
	* @param projetil - Ponteiro opicional ao projétil que causou o dano
	* @param Hit -  Estrutura com os resultados da colisão que causou o dano.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	/*
	* Interface para aplicar os stats do jogador ao projétil atirado.
	* @param projetil - Ponteiro ao projétil atirado.
	*/
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		virtual void ApplyProjectileStats(AProjectile* projectile) override;

	/* Evento de blueprint para o jogador atirar. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Atirar", Keywords = "Atirar"), Category = "Player")
		void FireGun();

	/* Evento de blueprint disparado quando o jogador morreu. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Player Morreu", Keywords = "Player Morreu"), Category = "Player")
		void OnPlayerDeath();

	/*
	* Evento de blueprint para gerar o pop up de dano.
	* @param dano - dano causado.
	* @param alvo - Enemy que foi atingido.
	* @param projetil - projetil que causou o dano
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar DanoPopUp", Keywords = "Gerar Dano PopUp"), Category = "Player")
		void GenerateDamagePopUp(float damage, AEnemy* target, AProjectile* projectile);

	/*
	* Evento de blueprint para gerar o pop up do pick up.
	* @param novoPickUp - Pick que foi pego.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar PickUp PopUp", Keywords = "Gerar PickUp PopUp"), Category = "Player")
		void GeneratePickUpPopUp(class APickUp* newPickUp);

	/*
	* Evento de blueprint para gerar o item de pop up.
	* @param novoItem - Item que foi pego.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar Item PopUp", Keywords = "Gerar Item PopUp"), Category = "Player")
		void GenerateItemPopUp(class AActor* newItem);
	/*
	* Evento de blueprint para gerar o semi círculo de dano.
	* @param Hit - Referência constante aos resultados de colisão que causou dano ao jogador.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gerar Circulo Dano", Keywords = "Gerar Circulo Dano"), Category = "Player")
		void GenerateDamageCircleUI(const FHitResult& Hit);

	/* Função para fazer o cooldown do item. Função para ser chamada durante o Tick do jogador.*/
	UFUNCTION()
		void ItemCooldown(float DeltaTime);

	/* Evento de blueprint para fazer o reset do timer de cooldown do item. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void ResetTimer();

};
