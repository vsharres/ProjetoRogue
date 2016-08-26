// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Boss.h"

ABoss::ABoss(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Initializing the properties
	EnemyType = EEnemyType::BOSS;
	Armor = 0.5f;

	//Attaching the weak point collision component
	WeakPoint = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("PontoFraco"));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	WeakPoint->AttachToComponent(GetMesh(),Rules);

}

void ABoss::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	this->FlashDamage(); //Flash boss material when damaged
	AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//if the hit was on the boss weak point, cause normal damage, if not caused reduced damaged based on the boss armor
	if (Hit.GetComponent() == WeakPoint) 
	{
		Stats.Health -= damage;
		if (player->IsValidLowLevelFast())
		{
			player->GenerateDamagePopUp(damage, this, projectile); //spawn damage pop up
		}
	}
	else
	{
		Stats.Health -= damage * Armor;
		if (player->IsValidLowLevelFast())
		{
			player->GenerateDamagePopUp(damage* Armor, this, projectile); //spawn damage pop up
		}
	}
	
}

void ABoss::CalculateStats(int32 currentLevel)
{
	//adjusting the stats
	Stats.Health += 100 * (currentLevel - 1);
	Stats.Damage += 10 * (currentLevel - 1);
	Stats.MaxHealth += 100 * (currentLevel - 1);
	Armor += 0.2f * (currentLevel - 1);
}

void ABoss::OnBossDefeated()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	//Instantiating the save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		//saving that the boss was defeated
		SaveInst->bIsBossDefeated = true;

	}

	//Saving to slot
	UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
}
