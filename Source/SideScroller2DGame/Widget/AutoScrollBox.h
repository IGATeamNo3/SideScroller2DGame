// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Components/ScrollBox.h"
#include "AutoScrollBox.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2DGAME_API UAutoScrollBox : public UScrollBox
{
	GENERATED_BODY()

public:
	UAutoScrollBox();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Auto Scroll Box")
		void SetActiveScroll(bool bNewActive, bool bReset);

	virtual void PostLoad() override;

private:
	void Activate(bool bReset);
	void Deactivate();
	bool ShouldActivate() const;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		uint8 bAutoActiveScroll : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		uint8 bLoop : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Scroll Box")
		float ScrollSpeed;

private:

	uint8 bIsActiveScroll : 1;
	
};
