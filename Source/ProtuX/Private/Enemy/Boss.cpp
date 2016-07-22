// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "Boss.h"

ABoss::ABoss(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Inicializando as propriedades
	EnemyType = EEnemyType::BOSS;
	Armor = 0.5f;

	WeakPoint = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("PontoFraco"));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	WeakPoint->AttachToComponent(GetMesh(),Rules);

}

void ABoss::ReceiveDamage(const float& damage, class AProjectile* projectile, const FHitResult& Hit)
{
	this->FlashDamage(); //fazer o flash do mesh do boss
	AProtuXPlayer* player = Cast<AProtuXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Hit.GetComponent() == WeakPoint) //se o ponto fraco do boss foi atingido, causar o dano normal, se não causar um dano reduzido
	{
		Stats.Health -= damage;
		if (player->IsValidLowLevelFast())
		{
			player->GenerateDamagePopUp(damage, this, projectile); //gerar o popup com o dano causado
		}
	}
	else
	{
		Stats.Health -= damage * Armor;
		if (player->IsValidLowLevelFast())
		{
			player->GenerateDamagePopUp(damage* Armor, this, projectile); //gerar o popup com o dano causado
		}
	}
	
}

void ABoss::CalculateStats(int32 currentLevel)
{
	Stats.Health += 100 * (currentLevel - 1);
	Stats.Damage += 10 * (currentLevel - 1);
	Stats.MaxHealth += 100 * (currentLevel - 1);
	Armor += 0.2f * (currentLevel - 1);
}

void ABoss::OnBossDefeated()
{
	AProtuXGameMode* gameMode = Cast<AProtuXGameMode>(UGameplayStatics::GetGameMode(this));

	//Criar o objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bIsBossDefeated = true;

	}

	//Salvar
	UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
}
