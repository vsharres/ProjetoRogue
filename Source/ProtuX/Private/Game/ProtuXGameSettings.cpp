// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtuX.h"
#include "ProtuXGameSettings.h"

UProtuXGameSettings::UProtuXGameSettings()
{
	//Initializing properties
	UserSettings = GetUserGameSettings();
}

UGameUserSettings* UProtuXGameSettings::GetUserGameSettings()
{
	if (GEngine != nullptr) //sanity check
	{
		return GEngine->GameUserSettings;
	}
	return nullptr;
}

bool UProtuXGameSettings::GetIsMuted()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));
	if (SaveInst)
	{
		return SaveInst->bMute;
	}

	return false;
}

float UProtuXGameSettings::GetMasterVol()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MasterVol; 
	}

	return 1.0f;
}

float UProtuXGameSettings::GetMusicVol()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MusicVol;
	}

	return 1.0f;
}

float UProtuXGameSettings::GetEffectVol()
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	
	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->EffectsVol;
	}

	return 1.0f;
}

int32 UProtuXGameSettings::GetQualitySettings()
{
	if (UserSettings) //checking if the player has changed the user settings
	{
		return UserSettings->ScalabilityQuality.EffectsQuality;
	}

	return 0;
}

bool UProtuXGameSettings::IsFullScreen()
{
	bool inFullscreen = true;

	if (UserSettings)
	{
		switch (UserSettings->GetLastConfirmedFullscreenMode()) //Get the last confirmed screen mode
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

bool UProtuXGameSettings::GetVSync()
{
	bool vsyncActive = true;

	if (UserSettings) //checking if the player has changed the user settings
	{
		vsyncActive = UserSettings->bUseVSync;
	}

	return vsyncActive;
}

FIntPoint UProtuXGameSettings::GetResolution()
{
	return (GEngine->GameViewport->Viewport->GetSizeXY()); //Current screen resolution
}

void UProtuXGameSettings::SetIsMuted(bool newMute)
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bMute = newMute;
		
		//Saving new properties
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

}

void UProtuXGameSettings::SetMasterVol(float newVol)
{
	//instantiate save game object
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//Loading property
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MasterVol = newVol;

		//Saving new properties
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}


void UProtuXGameSettings::SetQualitySettings(int32 newSetting)
{
	if (UserSettings) //checking if the player has changed the user settings
	{
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevel(newSetting);
	}
}

void UProtuXGameSettings::SetResolution(FIntPoint newResolution)
{
	if (UserSettings) //checking if the player has changed the user settings
	{
		UserSettings->SetScreenResolution(newResolution);
	}
}

void UProtuXGameSettings::SetFullScreenMode(bool bFullscreen)
{
	if (UserSettings) //checking if the player has changed the user settings
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

void UProtuXGameSettings::SetVSyncEnable(bool bEnable)
{
	if (UserSettings) //checking if the player has changed the user settings
	{
		UserSettings->SetVSyncEnabled(bEnable);
	}
}

void UProtuXGameSettings::ApplySettings(bool bApply)
{
	if (UserSettings)
	{
		if (bApply) //applying the user settings
		{
			UserSettings->ConfirmVideoMode(); //confirm video mode

			UserSettings->SetScreenResolution(UserSettings->GetLastConfirmedScreenResolution());
			UserSettings->SetFullscreenMode(UserSettings->GetLastConfirmedFullscreenMode());
			UserSettings->ApplySettings(false);
			UserSettings->SaveSettings(); //save new settings
		}
		else
		{
			UserSettings->RevertVideoMode(); //revert to last video mode, before the player had made any changes
		}
	}
}

