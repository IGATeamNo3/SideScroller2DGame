// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedUMGPrivatePCH.h"
#include "AutoScrollBoxSlot.h"
#include "AutoScrollBox.h"



#define LOCTEXT_NAMESPACE "UMG"
UAutoScrollBox::UAutoScrollBox()
{
	ScrollSpeed = 10.f;
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

void UAutoScrollBox::SetIsScrollLoop(bool bNewLoop)
{
	bLoop = bNewLoop;
}

void UAutoScrollBox::PostLoad()
{
	Super::PostLoad();
/*	if (bAutoActiveScroll)
	{
		Activate(true);
	}*/
}

void UAutoScrollBox::SynchronizeProperties()
{
	SetActiveScroll(bIsActiveScroll, true);
	Super::SynchronizeProperties();
}

UClass* UAutoScrollBox::GetSlotClass() const
{
	return UAutoScrollBoxSlot::StaticClass();
}

void UAutoScrollBox::OnSlotAdded(UPanelSlot* InSlot)
{
	if (MyAutoScrollBox.IsValid())
	{
		CastChecked<UAutoScrollBoxSlot>(InSlot)->BuildSlot(MyAutoScrollBox.ToSharedRef());
	}
}

void UAutoScrollBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (MyAutoScrollBox.IsValid())
	{
		TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
		if (Widget.IsValid())
		{
			MyAutoScrollBox->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

void UAutoScrollBox::Activate(bool bReset)
{
	if (bReset || ShouldActivate() == true)
	{
		bIsActiveScroll = true;
		
	}
	MyAutoScrollBox->SetActiveScroll(bIsActiveScroll, bReset);
}

void UAutoScrollBox::Deactivate()
{
	bIsActiveScroll = false;
	MyAutoScrollBox->SetActiveScroll(bIsActiveScroll, true);
}

bool UAutoScrollBox::ShouldActivate() const
{
	// if not active, should activate
	return !bIsActiveScroll;
}

TSharedRef<SWidget> UAutoScrollBox::RebuildWidget()
{
	MyAutoScrollBox = SNew(SAutoScrollBox)
		.bIsActiveScroll(bIsActiveScroll)
		.bLoop(bLoop)
		.ScrollSpeed(ScrollSpeed);
		//.Style(&WidgetStyle)
		//.ScrollBarStyle(&WidgetBarStyle)
		//.Orientation(Orientation)
		//.ConsumeMouseWheel(ConsumeMouseWheel);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (UAutoScrollBoxSlot* TypedSlot = Cast<UAutoScrollBoxSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyAutoScrollBox.ToSharedRef());
		}
	}

	return BuildDesignTimeWidget(MyAutoScrollBox.ToSharedRef());
}

#if WITH_EDITOR
const FText UAutoScrollBox::GetPaletteCategory()
{
	return LOCTEXT("Panel", "Panel");
}

void UAutoScrollBox::OnDescendantSelected(UWidget* DescendantWidget)
{

}

void UAutoScrollBox::OnDescendantDeselected(UWidget* DescendantWidget)
{

}
#endif

#undef LOCTEXT_NAMESPACE