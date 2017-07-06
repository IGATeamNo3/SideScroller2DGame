// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScroller2DGame.h"
#include "Keyboar_KeyboardViewportClient.h"




bool UKeyboar_KeyboardViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed /*= 1.f*/, bool bGamepad /*= false*/)
{
	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
	{
		return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
	}
	else
	{
		// Propagate keyboard events to all players
		UEngine* const Engine = GetOuterUEngine();
		int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRetVal = false;
		for (int32 i = 0; i < NumPlayers; i++)
		{
			bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
		}

		return bRetVal;
	}
}

bool UKeyboar_KeyboardViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples /*= 1*/, bool bGamepad /*= false*/)
{
	return Super::InputAxis(Viewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
}
