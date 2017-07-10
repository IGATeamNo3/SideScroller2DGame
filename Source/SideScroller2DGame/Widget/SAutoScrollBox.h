// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "InertialScrollManager.h"
#include "Overscroll.h"

/** SAutoScrollBox can scroll through an arbitrary number of widgets. */
class SIDESCROLLER2DGAME_API SAutoScrollBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAutoScrollBox)
	//: _Style(&FCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("ScrollBox"))
	{}
	SLATE_END_ARGS();


	//SLATE_STYLE_ARGUMENT(FSlateWidgetStyle, BoxStyle);

	void Construct(const FArguments& InArgs);


public:

	// SWidget interface
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/** Style resource for the scrollbox */
	//const FSlateWidgetStyle* BoxStyle;
};
