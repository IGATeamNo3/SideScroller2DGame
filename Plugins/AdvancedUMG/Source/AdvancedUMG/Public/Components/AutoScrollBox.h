// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "Runtime/UMG/Public/UMGStyle.h"
//#include "Components/ScrollBox.h"
#include "AutoScrollBox.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UAutoScrollBox : public UPanelWidget
{
	GENERATED_BODY()

public:
	UAutoScrollBox();
	UFUNCTION(BlueprintCallable, Category = "Auto Scroll Box")
	void SetActiveScroll(bool bNewActive, bool bReset);


	virtual void PostLoad() override;

#if WITH_EDITOR
	//~ Begin UWidget Interface
	virtual const FText GetPaletteCategory() override;
	virtual void OnDescendantSelected(UWidget* DescendantWidget) override;
	virtual void OnDescendantDeselected(UWidget* DescendantWidget) override;
	//~ End UWidget Interface
#endif

protected:

	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;
	// End UPanelWidget

private:
	void Activate(bool bReset);
	void Deactivate();
	bool ShouldActivate() const;
protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		uint8 bAutoActiveScroll : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		uint8 bLoop : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		float ScrollSpeed;

protected:
	TSharedPtr<class SAutoScrollBox> MyAutoScrollBox;
private:

	uint8 bIsActiveScroll : 1;
	
};
