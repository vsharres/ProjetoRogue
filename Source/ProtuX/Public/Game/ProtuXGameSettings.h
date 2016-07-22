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
	/* Constructor Padrão. */
	UProtuXGameSettings();
	
	/*
	* Função de Get dos settings atuais.
	* @return Ponteiro ao UGameUserSettings atual.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		UGameUserSettings* GetUserGameSettings();
	
	/*
	* Função do Get do Mudo.
	* @return booleano com o mudo.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetIsMuted();

	/*
	* Função do Get do volume total do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMasterVol();

	/*
	* Função do Get do volume da música do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetMusicVol();
	
	/*
	* Função do Get do volume dos efeitos do jogo.
	* @return float com o volume
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		float GetEffectVol();

	/*
	* Função do Get da qualidade gráfica do jogo.
	* @return valor inteiro que varia entre 0 a 3, sendo que (0=low, 1=medium, 2=high, 3=epic)
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		int32 GetQualitySettings();

	/*
	* Função para saber se a tela deve ser totalmente preenchida.
	* @return booleano indicando se a tela está preenchida.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool IsFullScreen();

	/*
	* Função para saber o VSync está ativado.
	* @return booleano indicando se o VSync está ativado.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		bool GetVSync();
	
	/*
	* Função de Get da resolução atual da tela.
	* @return FIntPoint, que é um vetor 2D com inteiros com a resolução atual.
	*/
	UFUNCTION(BlueprintPure, Category = "UserSettings")
		FIntPoint GetResolution();
	
	/*
	* Função de Set do mudo.
	* @param newMute - Booleano indicando se o jogo de ser mudo.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetIsMuted(bool newMute);
	
	/*
	* Função de Set do volume total do jogo.
	* @param newVol - float com o novo volume.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetMasterVol(float newVol);
	
	/*
	* Função de Set da qualidade gráfica.
	* @param newSetting - int32 com o novo setting gráfico.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetQualitySettings(int32 newSetting);
	
	/*
	* Função de Set da resolução da tela.
	* @param newResolution - FIntPoint com a nova resolução.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetResolution(FIntPoint newResolution);
	/*
	* Função de Set da tela totalmente preenchida.
	* @param bFullScreen - Booleano indicando se a tela deve ser preenchida.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetFullScreenMode(bool bFullScreen);
	
	/*
	* Função de Set do VSync
	* @param bFullScreen - Booleano indicando se o VSync deve ser ativado.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void SetVSyncEnable(bool bEnable);
	
	/*
	* Função para aplicar os settings escolhidos pelo jogador.
	* @param bApply - Booleano indicando se os settings devem ser ativados.
	*/
	UFUNCTION(BlueprintCallable, Category = "UserSettings")
		void ApplySettings(bool bApply);

};
