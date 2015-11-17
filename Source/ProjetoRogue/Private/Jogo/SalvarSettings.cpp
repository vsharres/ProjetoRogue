// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "SalvarSettings.h"


USalvarSettings::USalvarSettings()
{
	UserSettings = GetUserGameSettings();
}

UGameUserSettings* USalvarSettings::GetUserGameSettings()
{
	if (GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}
	return nullptr;
}

bool USalvarSettings::GetIsMuted()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));
	if (SaveInst)
	{
		return SaveInst->bMute;
	}

	return false;
}

float USalvarSettings::GetMasterVol()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MasterVol;
	}

	return 1.0f;
}

float USalvarSettings::GetMusicVol()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MusicVol;
	}

	return 1.0f;
}

float USalvarSettings::GetEffectVol()
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->EffectsVol;
	}

	return 1.0f;
}

int32 USalvarSettings::GetQualitySettings()
{
	if (UserSettings)
	{
		return UserSettings->ScalabilityQuality.EffectsQuality;
	}

	return 0;
}

bool USalvarSettings::IsFullScreen()
{
	bool inFullscreen = true;

	if (UserSettings)
	{
		switch (UserSettings->GetLastConfirmedFullscreenMode())
		{
		case EWindowMode::Type::Fullscreen:
			inFullscreen = true;
			break;
		default:
			inFullscreen = false;
			break;
		}

	}

	return inFullscreen;
}

bool USalvarSettings::GetVSync()
{
	bool vsyncActive = true;

	if (UserSettings)
	{
		vsyncActive = UserSettings->bUseVSync;
	}

	return vsyncActive;
}

FIntPoint USalvarSettings::GetResolution()
{
	return (GEngine->GameViewport->Viewport->GetSizeXY());
}

void USalvarSettings::SetIsMuted(bool newMute)
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bMute = newMute;
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

}

void USalvarSettings::SetMasterVol(float newVol)
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MasterVol = newVol;
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void USalvarSettings::SetMusicVol(float newVol)
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MusicVol = newVol;
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void USalvarSettings::SetEffectsVol(float newVol)
{
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->EffectsVol = newVol;
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void USalvarSettings::SetQualitySettings(int32 newSetting)
{
	if (UserSettings)
	{
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevel(newSetting);
	}
}

void USalvarSettings::SetResolution(FIntPoint newResolution)
{
	if (UserSettings)
	{
		UserSettings->SetScreenResolution(newResolution);
	}
}

void USalvarSettings::SetFullScreenMode(bool bFullscreen)
{
	if (UserSettings)
	{
		if (bFullscreen)
		{
			UserSettings->SetFullscreenMode(EWindowMode::Type::Fullscreen);

		}
		else
		{
			UserSettings->SetFullscreenMode(EWindowMode::Type::Windowed);
		}

	}
}

void USalvarSettings::SetVSyncEnable(bool bEnable)
{
	if (UserSettings)
	{
		UserSettings->SetVSyncEnabled(bEnable);
	}
}

void USalvarSettings::ApplySettings(bool bApply)
{
	if (UserSettings)
	{
		if (bApply)
		{
			UserSettings->ConfirmVideoMode();

			UserSettings->SetScreenResolution(UserSettings->GetLastConfirmedScreenResolution());
			UserSettings->SetFullscreenMode(UserSettings->GetLastConfirmedFullscreenMode());
			UserSettings->ApplySettings(false);
			UserSettings->SaveSettings();
		}
		else
		{
			UserSettings->RevertVideoMode();
		}
	}
}

