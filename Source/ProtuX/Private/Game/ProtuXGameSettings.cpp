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
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));
	if (SaveInst)
	{
		return SaveInst->bMute;
	}

	return false;
}

float UProtuXGameSettings::GetMasterVol()
{
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MasterVol;
	}

	return 1.0f;
}

float UProtuXGameSettings::GetMusicVol()
{
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MusicVol;
	}

	return 1.0f;
}

float UProtuXGameSettings::GetEffectVol()
{
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));
	
	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->EffectsVol;
	}

	return 1.0f;
}

int32 UProtuXGameSettings::GetQualitySettings()
{
	if (UserSettings)
	{
		return UserSettings->ScalabilityQuality.EffectsQuality; //Qualidade dos gráficos.
	}

	return 0;
}

bool UProtuXGameSettings::IsFullScreen()
{
	bool inFullscreen = true;

	if (UserSettings)
	{
		switch (UserSettings->GetLastConfirmedFullscreenMode()) //usando o último modo de tela escolhido pelo jogador
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

	if (UserSettings)
	{
		vsyncActive = UserSettings->bUseVSync;
	}

	return vsyncActive;
}

FIntPoint UProtuXGameSettings::GetResolution()
{
	return (GEngine->GameViewport->Viewport->GetSizeXY()); //Resolução atual da tela
}

void UProtuXGameSettings::SetIsMuted(bool newMute)
{
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bMute = newMute;
		//Salvando nova propriedade
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

}

void UProtuXGameSettings::SetMasterVol(float newVol)
{
	//criando objeto de save.
	UProtuXSaveGame* SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::CreateSaveGameObject(UProtuXSaveGame::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<UProtuXSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MasterVol = newVol;
		//Salvando nova propriedade
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}


void UProtuXGameSettings::SetQualitySettings(int32 newSetting)
{
	if (UserSettings)
	{
		UserSettings->ScalabilityQuality.SetFromSingleQualityLevel(newSetting);
	}
}

void UProtuXGameSettings::SetResolution(FIntPoint newResolution)
{
	if (UserSettings)
	{
		UserSettings->SetScreenResolution(newResolution);
	}
}

void UProtuXGameSettings::SetFullScreenMode(bool bFullscreen)
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

void UProtuXGameSettings::SetVSyncEnable(bool bEnable)
{
	if (UserSettings)
	{
		UserSettings->SetVSyncEnabled(bEnable);
	}
}

void UProtuXGameSettings::ApplySettings(bool bApply)
{
	if (UserSettings)
	{
		if (bApply) //Aplicando os novos settings.
		{
			UserSettings->ConfirmVideoMode(); //confirmando as opções visuais

			UserSettings->SetScreenResolution(UserSettings->GetLastConfirmedScreenResolution());
			UserSettings->SetFullscreenMode(UserSettings->GetLastConfirmedFullscreenMode());
			UserSettings->ApplySettings(false);
			UserSettings->SaveSettings(); //Salvando novos settings
		}
		else
		{
			UserSettings->RevertVideoMode(); //revertendo para o modo de vídeo anterior.
		}
	}
}

