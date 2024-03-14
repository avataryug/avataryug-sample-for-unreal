// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AdsData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "Components/TextBlock.h"
#include "AdsButton.generated.h"
DECLARE_DYNAMIC_DELEGATE_OneParam(FRewardItemClick,FAdsPlacementClass, data);
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UAdsButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton *ADP_RewardItemButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *RewardNameText;

	UFUNCTION()
    void OnClickRewardItemButton();
    UPROPERTY()
    FRewardItemClick OnRewardItemClick;
	UPROPERTY()
	FAdsPlacementClass item ;
};
