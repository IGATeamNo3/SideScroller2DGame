// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

/** SAutoScrollBox can scroll through an arbitrary number of widgets. */
class ADVANCEDUMG_API SAutoScrollBox : public SCompoundWidget
{
public:

	//Auto Scroll Slot
	class ADVANCEDUMG_API FSlot : public TSlotBase<FSlot>, public TSupportsContentPaddingMixin<FSlot>
	{
	public:
		FSlot()
			: TSlotBase<FSlot>()
			// Set both vertical and horizontal alignment to fill by default.  During layout, the
			// alignment direction parallel to the scroll direction is assumed to be top, or left
			// since that is how the items are stacked.
			, HAlignment(HAlign_Fill)
			, VAlignment(VAlign_Fill)
		{
		}

		FSlot& HAlign(EHorizontalAlignment InHAlignment)
		{
			HAlignment = InHAlignment;
			return *this;
		}

		FSlot& VAlign(EVerticalAlignment InVAlignment)
		{
			VAlignment = InVAlignment;
			return *this;
		}

		EHorizontalAlignment HAlignment;
		EVerticalAlignment VAlignment;
	};


	SLATE_BEGIN_ARGS(SAutoScrollBox)
		//: _Style(&FCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("ScrollBox"))
		: _Orientation(Orient_Vertical)
		, _OnUserScrolled()
		, _bIsActiveScroll(true)
		, _bLoop(true)
		, _ScrollSpeed(20.f)
		, _BoxSize(FVector2D())
	{}

	SLATE_ARGUMENT(FOnUserScrolled, OnUserScrolled);
	SLATE_ARGUMENT(EOrientation, Orientation);
	SLATE_ARGUMENT(bool, bIsActiveScroll);
	SLATE_ARGUMENT(float ,ScrollSpeed)
	SLATE_ARGUMENT(bool, bLoop);
	SLATE_ARGUMENT(FVector2D, BoxSize)

	SLATE_SUPPORTS_SLOT(FSlot)

	SLATE_END_ARGS();

public:
	//SLATE_STYLE_ARGUMENT(FSlateWidgetStyle, BoxStyle);

	void Construct(const FArguments& InArgs);

	static FSlot& Slot();

	SAutoScrollBox::FSlot& AddSlot();

	/** Removes a slot at the specified location */
	void RemoveSlot(const TSharedRef<SWidget>& WidgetToRemove);

	/** Removes all children from the box */
	void ClearChildren();

	// SWidget interface
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void SetActiveScroll(bool bNewActive, bool bReset);

private:
	/** Constructs internal layout widgets for scrolling vertically using the existing ScrollPanel and ScrollBar. */
	void ConstructVerticalLayout();

	/** Constructs internal layout widgets for scrolling horizontally using the existing ScrollPanel and ScrollBar. */
	void ConstructHorizontalLayout();

private:
	void Activate(bool bReset);
	void Deactivate();
	bool ShouldActivate() const;

private:

	/** The panel which stacks the child slots */
	TSharedPtr<class SAutoScrollPanel> AutoScrollPanel;

	EOrientation Orientation;

	/** Fired when the user scrolls the scrollbox */
	FOnUserScrolled OnUserScrolled;


	bool bAutoActiveScroll;

	bool bIsActiveScroll;

	bool bLoop;

	float ScrollSpeed;

	float time = 0.f;

	FVector2D BoxSize;
};
