// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Runtime/Core/Public/GenericPlatform/GenericWindow.h"
#include "SalvarSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJETOROGUE_API USalvarSettings : public UObject
{
	GENERATED_BODY()

private:

		UPROPERTY()
		UGameUserSettings* UserSettings;

public:
	
	USalvarSettings();
	
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		UGameUserSettings* GetUserGameSettings();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetIsMuted();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMasterVol();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMusicVol();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetEffectVol();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		int32 GetQualitySettings();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool IsFullScreen();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetVSync();

	UFUNCTION(BlueprintPure, Category = "UserSettings")
		FIntPoint GetResolution();

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetIsMuted(bool newMute);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetMasterVol(float newVol);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetMusicVol(float newVol);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetEffectsVol(float newVol);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetQualitySettings(int32 newSetting);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetResolution(FIntPoint newResolution);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetFullScreenMode(bool bFullScreen);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetVSyncEnable(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void ApplySettings(bool bApply);

};
