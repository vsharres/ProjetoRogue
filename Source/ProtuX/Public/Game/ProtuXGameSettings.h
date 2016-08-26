// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Runtime/Core/Public/GenericPlatform/GenericWindow.h"
#include "ProtuXGameSettings.generated.h"

/**
*	Class inherited from UObject
*	Class that manages the game setting. It changes video and audio settings.
 */
UCLASS(BlueprintType)
class PROTUX_API UProtuXGameSettings : public UObject
{
	GENERATED_BODY()

#pragma region Properties

private:
	/** Pointer to the current user settings. */ 
		UPROPERTY()
		UGameUserSettings* UserSettings;

#pragma endregion Properties

#pragma region Constructor

public:
	/** Default Constructor */
	UProtuXGameSettings();
#pragma endregion Constructor

#pragma region Functions
	
	/**
	* Function to get the current user settings
	* @return Pointer to the current user settings
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		UGameUserSettings* GetUserGameSettings();
	
	/**
	* Function to get the is muted boolean
	* @return boolean of true if the game is muted
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetIsMuted();

	/**
	* Function to get the master volume in the game
	* @return float with the master volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMasterVol();

	/**
	* Function to get the music volume in the game
	* @return float with the music volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMusicVol();
	
	/**
	* Function to get the effects volume in the game
	* @return float with the effects volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetEffectVol();

	/**
	* Function to get the graphics quality settings of the game
	* @return integer value between 0 and 3, where (0=low, 1=medium, 2=high, 3=epic)
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		int32 GetQualitySettings();

	/**
	* Function to get if the window is in full screen mode
	* @return boolean of true if the window is in full screen mode
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool IsFullScreen();

	/**
	* Function to get the VSync setting
	* @return boolean of true if VSync is activated
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetVSync();
	
	/**
	* Function to get the screen resolution
	* @return A 2D vector with the values of the resolution width and height.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		FIntPoint GetResolution();
	
	/**
	* Function to set is muted.
	* @param newMute - boolean of the new muted state
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetIsMuted(bool newMute);
	
	/**
	* Function to set the master volume of the game
	* @param newVol - float with the new value of the master volume
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetMasterVol(float newVol);
	
	/**
	* Function to set the quality settings
	* @param newSetting - new graphics setting  (between 0 and 3)
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetQualitySettings(int32 newSetting);
	
	/**
	* Function to set the screen resolution
	* @param newResolution - FIntPoint com with the new resolution.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetResolution(FIntPoint newResolution);
	/**
	* Function to set the window to full screen mode
	* @param bFullScreen - boolean to set the full screen mode
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetFullScreenMode(bool bFullScreen);
	
	/**
	* Function to set the VSync
	* @param bEnable - boolean value to enable the VSync
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetVSyncEnable(bool bEnable);
	
	/**
	* Function to apply the settings chosen by the player
	* @param bApply - Boolean value to apply settings
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void ApplySettings(bool bApply);

#pragma endregion Functions

};
