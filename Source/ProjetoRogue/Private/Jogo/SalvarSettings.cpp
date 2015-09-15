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

FIntPoint USalvarSettings::GetResolution()
{
	if (UserSettings)
	{
		return UserSettings->GetLastConfirmedScreenResolution();
	}

	return FIntPoint();
}

void USalvarSettings::SetQualitySettings(int32 newSetting)
{
	if (UserSettings)
	{
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevel(newSetting);
		UserSettings->SaveSettings();
	}
}

void USalvarSettings::SetResolution(FIntPoint newResolution)
{
	if (UserSettings)
	{
		UserSettings->SetScreenResolution(newResolution);
		UserSettings->SaveSettings();
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

		UserSettings->SaveSettings();
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

