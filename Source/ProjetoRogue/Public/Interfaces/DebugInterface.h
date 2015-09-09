// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DebugInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UDebugInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
};

class IDebugInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void Debug();

};
