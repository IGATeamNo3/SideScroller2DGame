// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SideScroller2DGame.h"
#include "SideScroller2DGameGameMode.h"
#include "SideScroller2DGameCharacter.h"

ASideScroller2DGameGameMode::ASideScroller2DGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
