// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Runtime/Core/Public/GenericPlatform/GenericWindow.h"
#include "ProtuXGameSettings.generated.h"

/**
 * Classe utilizada para determinar com os settings do jogo.
 */
UCLASS(BlueprintType)
class PROTUX_API UProtuXGameSettings : public UObject
{
	GENERATED_BODY()

private:
	/* Ponteiro aos settings atuais do jogador. */ 
		UPROPERTY()
		UGameUserSettings* UserSettings;

public:
	/* Constructor Padr�o. */
	UProtuXGameSettings();
	
	/*
	* Fun��o de Get dos settings atuais.
	* @return Ponteiro ao UGameUserSettings atual.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		UGameUserSettings* GetUserGameSettings();
	
	/*
	* Fun��o do Get do Mudo.
	* @return booleano com o mudo.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetIsMuted();

	/*
	* Fun��o do Get do volume total do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMasterVol();

	/*
	* Fun��o do Get do volume da m�sica do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMusicVol();
	
	/*
	* Fun��o do Get do volume dos efeitos do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetEffectVol();

	/*
	* Fun��o do Get da qualidade gr�fica do jogo.
	* @return valor inteiro que varia entre 0 a 3, sendo que (0=low, 1=medium, 2=high, 3=epic)
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		int32 GetQualitySettings();

	/*
	* Fun��o para saber se a tela deve ser totalmente preenchida.
	* @return booleano indicando se a tela est� preenchida.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool IsFullScreen();

	/*
	* Fun��o para saber o VSync est� ativado.
	* @return booleano indicando se o VSync est� ativado.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetVSync();
	
	/*
	* Fun��o de Get da resolu��o atual da tela.
	* @return FIntPoint, que � um vetor 2D com inteiros com a resolu��o atual.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		FIntPoint GetResolution();
	
	/*
	* Fun��o de Set do mudo.
	* @param newMute - Booleano indicando se o jogo de ser mudo.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetIsMuted(bool newMute);
	
	/*
	* Fun��o de Set do volume total do jogo.
	* @param newVol - float com o novo volume.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetMasterVol(float newVol);
	
	/*
	* Fun��o de Set da qualidade gr�fica.
	* @param newSetting - int32 com o novo setting gr�fico.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetQualitySettings(int32 newSetting);
	
	/*
	* Fun��o de Set da resolu��o da tela.
	* @param newResolution - FIntPoint com a nova resolu��o.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetResolution(FIntPoint newResolution);
	/*
	* Fun��o de Set da tela totalmente preenchida.
	* @param bFullScreen - Booleano indicando se a tela deve ser preenchida.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetFullScreenMode(bool bFullScreen);
	
	/*
	* Fun��o de Set do VSync
	* @param bFullScreen - Booleano indicando se o VSync deve ser ativado.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetVSyncEnable(bool bEnable);
	
	/*
	* Fun��o para aplicar os settings escolhidos pelo jogador.
	* @param bApply - Booleano indicando se os settings devem ser ativados.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void ApplySettings(bool bApply);

};
