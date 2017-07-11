// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.


#include "SideScroller2DGame.h"
#include "AutoScrollBoxSlot.h"



/////////////////////////////////////////////////////
// UAutoScrollBoxSlot
UAutoScrollBoxSlot::UAutoScrollBoxSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAutoScrollBoxSlot::SetPadding(FMargin InPadding)
{
	Padding = InPadding;
	if (Slot)
	{
		Slot->Padding(InPadding);
	}
}

void UAutoScrollBoxSlot::SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Slot)
	{
		Slot->HAlign(InHorizontalAlignment);
	}
}

void UAutoScrollBoxSlot::SynchronizeProperties()
{
	SetPadding(Padding);
	SetHorizontalAlignment(HorizontalAlignment);
}

void UAutoScrollBoxSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Slot = nullptr;
}
void UAutoScrollBoxSlot::BuildSlot(TSharedRef<SAutoScrollBox> ScrollBox)
{
	Slot = &ScrollBox->AddSlot()
		.Padding(Padding)
		.HAlign(HorizontalAlignment)
		[
			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
		];
}
