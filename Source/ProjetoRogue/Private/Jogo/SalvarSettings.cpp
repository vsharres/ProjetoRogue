// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoRogue.h"
#include "SalvarSettings.h"


USalvarSettings::USalvarSettings()
{
	//Inicializando as propriedades, pegando os settings atuais do jogador.
	UserSettings = GetUserGameSettings();
}

UGameUserSettings* USalvarSettings::GetUserGameSettings()
{
	if (GEngine != nullptr) //Checando validade do ponteiro da instancia do jogo.
	{
		return GEngine->GameUserSettings;
	}
	return nullptr;
}

bool USalvarSettings::GetIsMuted()
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));
	if (SaveInst)
	{
		return SaveInst->bMute;
	}

	return false;
}

float USalvarSettings::GetMasterVol()
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MasterVol;
	}

	return 1.0f;
}

float USalvarSettings::GetMusicVol()
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		return SaveInst->MusicVol;
	}

	return 1.0f;
}

float USalvarSettings::GetEffectVol()
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));
	
	//carregando propriedades.
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
		return UserSettings->ScalabilityQuality.EffectsQuality; //Qualidade dos gráficos.
	}

	return 0;
}

bool USalvarSettings::IsFullScreen()
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
	return (GEngine->GameViewport->Viewport->GetSizeXY()); //Resolução atual da tela
}

void USalvarSettings::SetIsMuted(bool newMute)
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->bMute = newMute;
		//Salvando nova propriedade
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}

}

void USalvarSettings::SetMasterVol(float newVol)
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MasterVol = newVol;
		//Salvando nova propriedade
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void USalvarSettings::SetMusicVol(float newVol)
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->MusicVol = newVol;
		//Salvando nova propriedade
		UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlot, SaveInst->Userindex);
	}
}

void USalvarSettings::SetEffectsVol(float newVol)
{
	//criando objeto de save.
	USalvarJogo* SaveInst = Cast<USalvarJogo>(UGameplayStatics::CreateSaveGameObject(USalvarJogo::StaticClass()));

	//carregando propriedades.
	SaveInst = Cast<USalvarJogo>(UGameplayStatics::LoadGameFromSlot(SaveInst->SaveSlot, SaveInst->Userindex));

	if (SaveInst)
	{
		SaveInst->EffectsVol = newVol;
		//Salvando nova propriedade
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

