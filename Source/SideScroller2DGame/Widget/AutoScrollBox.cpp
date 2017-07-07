// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScroller2DGame.h"
#include "AutoScrollBox.h"




UAutoScrollBox::UAutoScrollBox()
{
	ScrollSpeed = 0.f;
}

void UAutoScrollBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//Super::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if (bIsActiveScroll)
	{
		SetScrollOffset(GetScrollOffset() - ScrollSpeed*InDeltaTime);
		//ScrollSpeed * InDeltaTime;
	}
}

void UAutoScrollBox::SetActiveScroll(bool bNewActive, bool bReset)
{

	// if it wants to activate
	if (bNewActive)
	{
		// make sure to check if it should activate
		Activate(bReset);
	}
		// otherwise, make sure it shouldn't activate
	else
	{
		Deactivate();
	}


}

void UAutoScrollBox::PostLoad()
{
	Super::PostLoad();
	if (bAutoActiveScroll)
	{
		Activate(true);
	}
}

void UAutoScrollBox::Activate(bool bReset)
{
	if (bReset || ShouldActivate() == true)
	{
		bIsActiveScroll = true;
		//
	}
}

void UAutoScrollBox::Deactivate()
{
	bIsActiveScroll = false;
}

bool UAutoScrollBox::ShouldActivate() const
{
	// if not active, should activate
	return !bIsActiveScroll;
}
