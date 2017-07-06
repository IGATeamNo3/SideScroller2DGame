// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Viewport/Keyboar_PadGameViewportClient.h"
#include "Keyboar_KeyboardViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2DGAME_API UKeyboar_KeyboardViewportClient : public UKeyboar_PadGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
	virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) override;

	
	
};
