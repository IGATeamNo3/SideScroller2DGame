// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "InertialScrollManager.h"
#include "Overscroll.h"

/** SScrollBox can scroll through an arbitrary number of widgets. */
class SLATE_API SAutoScrollBox : public SScrollBox
{
public:
	// SWidget interface
	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
};
