// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SideScroller2DGame.h"
#include "SAutoScrollBox.h"
#include "LayoutUtils.h"



class SAutoScrollPanel : public SPanel
{
public:

	SLATE_BEGIN_ARGS(SAutoScrollPanel)
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
	}

	SLATE_ARGUMENT(EOrientation, Orientation)

		SLATE_END_ARGS()

		SAutoScrollPanel()
		: Children()
	{
	}

	void Construct(const FArguments& InArgs, const TArray<SAutoScrollBox::FSlot*>& InSlots)
	{
		PhysicalOffset = 0;
		Children.Reserve(InSlots.Num());
		for (int32 SlotIndex = 0; SlotIndex < InSlots.Num(); ++SlotIndex)
		{
			Children.Add(InSlots[SlotIndex]);
		}
		Orientation = InArgs._Orientation;
	}

public:

	EOrientation GetOrientation()
	{
		return Orientation;
	}

	void SetOrientation(EOrientation InOrientation)
	{
		Orientation = InOrientation;
	}

	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override
	{
		float CurChildOffset = -PhysicalOffset;

		for (int32 SlotIndex = 0; SlotIndex < Children.Num(); ++SlotIndex)
		{
			const SAutoScrollBox::FSlot& ThisSlot = Children[SlotIndex];
			const EVisibility ChildVisibility = ThisSlot.GetWidget()->GetVisibility();

			if (ChildVisibility != EVisibility::Collapsed)
			{
				if (Orientation == Orient_Vertical)
				{
					CurChildOffset = ArrangeChildVerticalAndReturnOffset(AllottedGeometry, ArrangedChildren, ThisSlot, CurChildOffset);
				}
				else
				{
					CurChildOffset = ArrangeChildHorizontalAndReturnOffset(AllottedGeometry, ArrangedChildren, ThisSlot, CurChildOffset);
				}
			}
		}
	}


	virtual FVector2D ComputeDesiredSize(float) const override
	{
		FVector2D ThisDesiredSize = FVector2D::ZeroVector;
		for (int32 SlotIndex = 0; SlotIndex < Children.Num(); ++SlotIndex)
		{
			const SAutoScrollBox::FSlot& ThisSlot = Children[SlotIndex];
			if (ThisSlot.GetWidget()->GetVisibility() != EVisibility::Collapsed)
			{
				const FVector2D ChildDesiredSize = ThisSlot.GetWidget()->GetDesiredSize();
				if (Orientation == Orient_Vertical)
				{
					ThisDesiredSize.X = FMath::Max(ChildDesiredSize.X, ThisDesiredSize.X);
					ThisDesiredSize.Y += ChildDesiredSize.Y + ThisSlot.SlotPadding.Get().GetTotalSpaceAlong<Orient_Vertical>();
				}
				else
				{
					ThisDesiredSize.X += ChildDesiredSize.X + ThisSlot.SlotPadding.Get().GetTotalSpaceAlong<Orient_Horizontal>();
					ThisDesiredSize.Y = FMath::Max(ChildDesiredSize.Y, ThisDesiredSize.Y);
				}
			}
		}

		return ThisDesiredSize;
	}

	virtual FChildren* GetChildren() override
	{
		return &Children;
	}

	float PhysicalOffset;
	TPanelChildren<SAutoScrollBox::FSlot> Children;

private:

	float ArrangeChildVerticalAndReturnOffset(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren, const SAutoScrollBox::FSlot& ThisSlot, float CurChildOffset) const
	{
		const FMargin& ThisPadding = ThisSlot.SlotPadding.Get();
		const FVector2D& WidgetDesiredSize = ThisSlot.GetWidget()->GetDesiredSize();
		const float ThisSlotDesiredHeight = WidgetDesiredSize.Y + ThisPadding.GetTotalSpaceAlong<Orient_Vertical>();

		// Figure out the size and local position of the child within the slot.  There is no vertical alignment, because 
		// it does not make sense in a panel where items are stacked vertically end-to-end.
		AlignmentArrangeResult XAlignmentResult = AlignChild<Orient_Horizontal>(AllottedGeometry.Size.X, ThisSlot, ThisPadding);

		ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(ThisSlot.GetWidget(), FVector2D(XAlignmentResult.Offset, CurChildOffset + ThisPadding.Top), FVector2D(XAlignmentResult.Size, WidgetDesiredSize.Y)));
		return CurChildOffset + ThisSlotDesiredHeight;
	}

	float ArrangeChildHorizontalAndReturnOffset(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren, const SAutoScrollBox::FSlot& ThisSlot, float CurChildOffset) const
	{
		const FMargin& ThisPadding = ThisSlot.SlotPadding.Get();
		const FVector2D& WidgetDesiredSize = ThisSlot.GetWidget()->GetDesiredSize();
		const float ThisSlotDesiredWidth = WidgetDesiredSize.X + ThisPadding.GetTotalSpaceAlong<Orient_Horizontal>();

		// Figure out the size and local position of the child within the slot.  There is no horizontal alignment, because
		// it doesn't make sense in a panel where items are stacked horizontally end-to-end.
		AlignmentArrangeResult YAlignmentResult = AlignChild<Orient_Vertical>(AllottedGeometry.Size.Y, ThisSlot, ThisPadding);

		ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(ThisSlot.GetWidget(), FVector2D(CurChildOffset + ThisPadding.Left, YAlignmentResult.Offset), FVector2D(WidgetDesiredSize.X, YAlignmentResult.Size)));
		return CurChildOffset + ThisSlotDesiredWidth;
	}

private:

	EOrientation Orientation;
};


void SAutoScrollBox::Construct(const FArguments& InArgs)
{
	Orientation = InArgs._Orientation;
	OnUserScrolled = InArgs._OnUserScrolled;
	SAssignNew(AutoScrollPanel, SAutoScrollPanel, InArgs.Slots)
		.Orientation(Orientation);
	if (Orientation == Orient_Vertical)
	{
		ConstructVerticalLayout();
	}
	else
	{
		ConstructHorizontalLayout();
	}
}

void SAutoScrollBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//CurrentOffeset = CurrentOffeset - InDeltaTime * 15.f;
	Overscroll.ScrollBy(5.f);
	OnUserScrolled.ExecuteIfBound(0.5f);
	AutoScrollPanel->PhysicalOffset = 5.f;
	
}

void SAutoScrollBox::ConstructHorizontalLayout()
{
	TSharedPtr<SHorizontalBox> PanelAndScrollbar;
	this->ChildSlot
	[
		SAssignNew(PanelAndScrollbar, SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(SOverlay)

				+SOverlay::Slot()
				.Padding(FMargin(0.f,0.f,0.f,1.f))
				[
					AutoScrollPanel.ToSharedRef()
				]
			]
	];

}

void SAutoScrollBox::ConstructVerticalLayout()
{
	TSharedPtr<SVerticalBox> PanelAndScrollbar;
	this->ChildSlot
	[
		SAssignNew(PanelAndScrollbar, SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.Padding(FMargin(0.f, 0.f, 1.f, 0.f))
			[
				AutoScrollPanel.ToSharedRef()
			]
		]
	];
}

SAutoScrollBox::FSlot& SAutoScrollBox::Slot()
{
	return *(new SAutoScrollBox::FSlot());
}
/** Adds a slot to SScrollBox */
SAutoScrollBox::FSlot& SAutoScrollBox::AddSlot()
{
	SAutoScrollBox::FSlot& NewSlot = *new SAutoScrollBox::FSlot();
	AutoScrollPanel->Children.Add(&NewSlot);

	return NewSlot;
}
/** Removes a slot at the specified location */
void SAutoScrollBox::RemoveSlot(const TSharedRef<SWidget>& WidgetToRemove)
{
	TPanelChildren<SAutoScrollBox::FSlot>& Children = AutoScrollPanel->Children;
	for (int32 SlotIndex = 0; SlotIndex < Children.Num(); ++SlotIndex)
	{
		if (Children[SlotIndex].GetWidget() == WidgetToRemove)
		{
			Children.RemoveAt(SlotIndex);
			return;
		}
	}
}

void SAutoScrollBox::ClearChildren()
{
	AutoScrollPanel->Children.Empty();
}
