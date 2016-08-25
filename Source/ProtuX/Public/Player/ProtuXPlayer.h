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

/** Struct that holds the player stats. */
USTRUCT()
struct FPlayerStats
{
	GENERATED_USTRUCT_BODY()

	/* Player current health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Player Struct")
		float Health;

	/** Player max health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "50.0", ClampMax = "500.0", UIMin = "50.0", UIMax = "500.0"), Category = "Player Struct")
		float MaxHealth;

	/** Player current energy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Player Struct")
		float Energy;

	/** Player max energy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"), Category = "Player Struct")
		float MaxEnergy;

	/** Player movement speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "600.0", ClampMax = "1800.0", UIMin = "600.0", UIMax = "1800.0"), Category = "Player Struct")
		float Speed;

	/** Damage caused by the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "5.0", ClampMax = "50.0", UIMin = "5.0", UIMax = "50.0"), Category = "Player Struct")
		float Damage;

	/** Player fire rate.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0"), Category = "Player Struct")
		float FireRate;

	/** Player shooting accuracy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "30.0", UIMin = "1.0", UIMax = "30.0"), Category = "Player Struct")
		float Accuracy;

	/** Player projectile muzzle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1000.0", ClampMax = "7000.0", UIMin = "1000.0", UIMax = "7000.0"), Category = "Player Struct")
		float MuzzleSpeed;

	/** Add and assign operator overload to facilitate changing of player stats based on items added. */
	FORCEINLINE FPlayerStats& operator+=(const FItemStats& itemStats)
	{
		this->MaxHealth += itemStats.AddMaxHealth;
		this->MaxEnergy += itemStats.AddMaxEnergy;
		this->Speed += itemStats.AddSpeed;
		this->FireRate += itemStats.AddFireRate;
		this->Damage += itemStats.AddDamage;
		this->Accuracy += itemStats.AddAccuracy;
		this->MuzzleSpeed += itemStats.AddMuzzleSpeed;

		AddEnergy(itemStats.AddEnergy); //Adding the item energy
		AddHealth(itemStats.AddHealth); //Adding the item health

		ClampValues(); //clamp values to guarantee valid values

		return *this;
	}

	/** Subtract and assign operator overload to facilitate changing player stats based on items removed. */
	FORCEINLINE FPlayerStats& operator-=(const FItemStats& itemStats)
	{
		this->MaxHealth -= itemStats.AddMaxHealth;
		this->MaxEnergy -= itemStats.AddMaxEnergy;
		this->Speed -= itemStats.AddSpeed;
		this->FireRate -= itemStats.AddFireRate;
		this->Damage -= itemStats.AddDamage;
		this->Accuracy -= itemStats.AddAccuracy;
		this->MuzzleSpeed -= itemStats.AddMuzzleSpeed;

		AddEnergy(-itemStats.AddEnergy); //removing the item energy
		AddHealth(-itemStats.AddHealth); //removing the item health

		ClampValues(); //clamp values to guarantee valid values

		return *this;
	}

	/**
	* Function to clamp stats values to be added, this function is used when items are applied.
	* @param itemStats - Item stats to be added.
	* @return new calculated stats.
	*/
	FORCEINLINE FItemStats ClampAddStats(const FItemStats& itemStats)
	{
		FItemStats toReturn;

		if (itemStats.AddDamage + this->Damage > DAMAGE_MAX) //clamp max damage
		{
			toReturn.AddDamage = DAMAGE_MAX - this->Damage;
		}
		else if (itemStats.AddDamage + this->Damage < DAMAGE_MIN) //clamp min damage
		{
			toReturn.AddDamage = DAMAGE_MIN - this->Damage;
		}
		else
		{
			toReturn.AddDamage = itemStats.AddDamage;
		}

		if (itemStats.AddFireRate + this->FireRate > FIRERATE_MAX) //clamp max fire rate
		{
			toReturn.AddFireRate = FIRERATE_MAX - this->FireRate;
		}
		else if (itemStats.AddFireRate + this->FireRate < FIRERATE_MIN) // clamp min fire rate
		{
			toReturn.AddFireRate = FIRERATE_MIN - this->FireRate;
		}
		else
		{
			toReturn.AddFireRate = itemStats.AddFireRate;
		}

		if (itemStats.AddAccuracy + this->Accuracy > ACCURACY_MAX) //clamp max accuracy
		{
			toReturn.AddAccuracy = ACCURACY_MAX - this->Accuracy;
		}
		else if (itemStats.AddAccuracy + this->Accuracy < ACCURACY_MIN) //clamp min accuracy
		{
			toReturn.AddAccuracy = ACCURACY_MIN - this->Accuracy;
		}
		else
		{
			toReturn.AddAccuracy = itemStats.AddAccuracy;
		}

		if (itemStats.AddSpeed + this->Speed > SPEED_MAX) //clamp max movement speed
		{
			toReturn.AddHealth = SPEED_MAX - this->Speed;
		}
		else if (itemStats.AddSpeed + this->Speed < SPEED_MIN) //clamp min movement speed
		{
			toReturn.AddSpeed = SPEED_MIN - this->Speed;
		}
		else
		{
			toReturn.AddSpeed = itemStats.AddSpeed;
		}

		if (itemStats.AddMuzzleSpeed + this->MuzzleSpeed > MUZZLESPEED_MAX) //clamp max muzzle speed
		{
			toReturn.AddMuzzleSpeed = MUZZLESPEED_MAX - this->MuzzleSpeed;
		}
		else if (itemStats.AddMuzzleSpeed + this->MuzzleSpeed < MUZZLESPEED_MIN) //clamp min muzzle speed
		{
			toReturn.AddMuzzleSpeed = MUZZLESPEED_MIN - this->MuzzleSpeed;
		}
		else
		{
			toReturn.AddMuzzleSpeed = itemStats.AddMuzzleSpeed;
		}

		if (itemStats.AddMaxHealth + this->MaxHealth > MAXHEALTH_MAX) //clamp max health
		{
			toReturn.AddMaxHealth = MAXHEALTH_MAX - this->MaxHealth;
		}
		else if (itemStats.AddMaxHealth + this->MaxHealth < MAXHEALTH_MIN) //clamp min health
		{
			toReturn.AddMaxHealth = MAXHEALTH_MIN - this->MaxHealth;
		}
		else
		{
			toReturn.AddMaxHealth = itemStats.AddMaxHealth;
		}

		if (itemStats.AddHealth + this->Health > MaxHealth) //clamp current health
		{
			toReturn.AddHealth = MaxHealth - this->Health;
		}
		else if (itemStats.AddHealth + this->Health < MAXHEALTH_MIN) //clamp min current health
		{
			toReturn.AddHealth = MAXHEALTH_MIN - this->Health;
		}
		else
		{
			toReturn.AddHealth = itemStats.AddHealth;
		}

		if (itemStats.AddMaxEnergy + this->MaxEnergy > ENERGY_MAX) //clamp max energy
		{
			toReturn.AddMaxEnergy = ENERGY_MAX - this->MaxEnergy;
		}
		else if (itemStats.AddMaxEnergy + this->MaxEnergy < ENERGY_MIN) //clamp min energy
		{
			toReturn.AddMaxEnergy = ENERGY_MIN - this->MaxEnergy;
		}
		else
		{
			toReturn.AddMaxEnergy = itemStats.AddMaxEnergy;
		}

		if (itemStats.AddEnergy + this->Energy > MaxEnergy) // clamp max current energy
		{
			toReturn.AddEnergy = MaxEnergy - this->Energy;
		}
		else if (itemStats.AddEnergy + this->Energy < ENERGY_MIN) //clamp min current energy
		{
			toReturn.AddEnergy = ENERGY_MIN - this->Energy;
		}
		else
		{
			toReturn.AddEnergy = itemStats.AddEnergy;
		}

		return toReturn;
	}

	/**
	* Function to guarantee that stats values are clamped on valid values.
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

	/**
	* Function to add health to the stats.
	* @param healthAdd - Health to be added.
	*/
	FORCEINLINE void AddHealth(float healthAdd)
	{
		Health += healthAdd;

		if (Health > MaxHealth) //clamp values
		{
			Health = MaxHealth;
		}
		else if (Health < 0)
		{
			Health = 0;
		}

	}

	/**
	* Function to add energy to the stats.
	* @param energidaAdicionada - Energy to be added.
	*/
	FORCEINLINE void AddEnergy(float energyAdded)
	{
		Energy += energyAdded;

		if (Energy > MaxEnergy) //clamp values
		{
			Energy = MaxEnergy;
		}
		else if (Energy < 0)
		{
			Energy = 0;
		}
	}

	/**
	* Function to set new stats.
	* @param stats - New stats.
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

		ClampValues();
	}

	/** Default Constructor */
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

		ClampValues();
	}

	/** Copy Constructor */
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

		ClampValues();
	}

};

/** Enum of the types of interaction the player can make. */
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

/** Enum of the type of tutorial prompt. */
UENUM(BlueprintType)
enum class ETutorialPrompt :uint8
{
	BOSSDOOR,
	KEY,
	SHOP,
	PASSIVEITEM,
	ACTIVEITEM,
	INVENTORY
};

/** Enum of the type of initialization state  */
UENUM(BlueprintType)
enum class EInitializationState :uint8
{
	BOOTUP,
	NEWLEVEL,
	PLAY,
};

/**
* Class inherited from ACharacter.
* Class responsible for player functionality, some part of logic is also in the blueprints of the class.
*/
UCLASS()
class PROTUX_API AProtuXPlayer : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	/** Name of the current ProtuX */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FString Name;

	/** Player stats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FPlayerStats Stats;

	/** Player total scrap(Scrap) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 Coins;

	/** Active item current cooldown */
	UPROPERTY(BlueprintReadWrite, Category = "Item")
		float CurCooldown;

	/** Active item cooldown time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "5.0"), Category = "Item")
		float CooldownTime;

	/** Active item cooldown change rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.1", UIMax = "10.0"), Category = "Item")
		float CooldDownRate;

	/** Boolean of true if the player has found the boss room key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bHasKey;

	/** Passive items array */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<class UPassiveItem*> PassiveItems;

	/** Boolean of true if the player has found the level item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bFoundItem;

	/** Number of projectiles in the projectile pool */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
		int32 NumProjectiles;

	/** Class of the starting projectile */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class UProjectileItem> StartingProjectile;

	/** Class of the found projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<UProjectileItem> FoundProjectile;

	/** Current projectile used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UProjectileItem* CurrentProjectile;

	/** Projectile pool array. This pool is static, i.e; all projectiles are alocated when a new projectile item is applied */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TArray<AProjectile*> ProjectilePool;

	/** Cannon socket name from where the projectiles are shoot from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		FName ProjectileSocket;

	/** Projectiles current color */
	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
		FLinearColor ProjectileColor;

	/** Default Constructor */
	AProtuXPlayer(const FObjectInitializer& ObjectInitializer);

	/**
	* Function to initialize the player
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void InitializePlayer();

	/**
	* Function to generate the name of the current version of the player's ProtuX
	* @param index - Number of the current version.
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void GenerateName(int32 index);

	/**
	* Function to update the movement properties of the projectiles with the current player stats.
	*/
	UFUNCTION()
		void UpdateProjectileStats();

	/**
	* Function to initialize a projectile inside the projectile pool
	* @param bIsDeactivated - Boolean to deactivate a projectile
	*/
	UFUNCTION()
		void InitializeProjectile(bool bIsDeactivated = false);

	/**
	* Function to generate the projectile pool
	*/
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void GenerateProjectilePool();

	/**
	* Function to check if the player is still alive
	* @return Boolean value of true if the player is alive
	*/
	UFUNCTION(BlueprintPure, Category = "Player")
		bool IsAlive();

	/**
	* Function to add health to the player
	* @param health - Health to be added
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddHealth(float health);
	/**
	* Function to add energy to the player
	* @param energy - Energy to be added
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddEnergy(float energy);

	/**
	* Function to add scrap to the player
	* @param value - scrap to be added
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddCoins(int32 value);

	/**
	* Function to save player state
	*/
	UFUNCTION(BlueprintCallable, Category = "Game")
		void SavePlayerState();

	/**
	* Function to load player state
	*/
	UFUNCTION(BlueprintCallable, Category = "Game")
		void LoadPlayerState();

	/**
	* Function to create the properties of a new player
	*/
	UFUNCTION(BlueprintCallable, Category = "Game")
		void NewPlayer();

	/**
	* Function to use an active item.
	* @param bIsDeactivated - Argument used to deactivate the item
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		void UseItem(bool bIsDeactivated = false);

	/**
	* Event to update the cannon mesh when an active item is activated
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void UpdateMesh();

	//INTERFACES

	/** Override of the player tick */
	virtual void Tick(float DeltaSeconds) override;

	/** Overload of the EndPlay player event */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	* Interface for the player to receive damage
	* @param damage - Damage received
	* @param projectile - Projectile that caused the damage(can be null when the damage was caused by melee)
	* @param Hit -  Hit 
	*/
	UFUNCTION(BlueprintCallable, Category = "Player")
		virtual void ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit) override;

	/**
	* Interface to apply the player stats to fired projectile
	* @param projectile - Pointer to the fired projectile
	*/
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		virtual void ApplyProjectileStats(AProjectile* projectile) override;

	/** Blueprint event to fire player gun */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Fire Gun", Keywords = "Fire"), Category = "Player")
		void FireGun();

	/** Blueprint event triggered on player death */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "On Player Death", Keywords = "Player Death"), Category = "Player")
		void OnPlayerDeath();

	/**
	* Blueprint event to spawn a damage pop up on enemies
	* @param damage - Damage caused.
	* @param target - Enemy that was hit by projectile
	* @param projectile - Projectile that caused damage
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gen Damage PopUp", Keywords = "Generate Damage PopUp"), Category = "Player")
		void GenerateDamagePopUp(float damage, AEnemy* target, AProjectile* projectile);

	/**
	* Blueprint event to spawn a PickUp pop up.
	* @param newPickUp - New PickUp found
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gen PickUp PopUp", Keywords = "Generate PickUp PopUp"), Category = "Player")
		void GeneratePickUpPopUp(class APickUp* newPickUp);

	/**
	* Blueprint Event to spawn a item pop up
	* @param newItem - New Item found
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gen Item PopUp", Keywords = "Generate Item PopUp"), Category = "Player")
		void GenerateItemPopUp(class AActor* newItem);
	/**
	* Blueprint event to spawn the damage semi-circle
	* @param Hit - Hit result to the enemy that caused damage to the player
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Gen Dmg Circle", Keywords = "Generate Damage Cirlce"), Category = "Player")
		void GenerateDamageCircleUI(const FHitResult& Hit);

	/** 
	* Function to update the item cooldown during the player's Tick.
	* @param DeltaTime - Update time
	*/
	UFUNCTION()
		void ItemCooldown(float DeltaTime);

	/** Blueprint event to reset the cooldown timer */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void ResetTimer();

};
