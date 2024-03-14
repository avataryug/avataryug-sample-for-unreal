// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "BundleDetailPanel.h"
#include "BundlesData.h"
#include "BundleButton.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBundleButton : public UUserWidget
{
	GENERATED_BODY()


	protected:
	void NativeConstruct() override;


	public:
	UPROPERTY(meta = (BindWidget))
	class UButton *BundleItemBtn;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *BIB_BundleNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *BIB_BundleCoinText;

	UPROPERTY()
    FEconomyBundle currentData;

	UFUNCTION()
    void SetButton(FEconomyBundle data, UBundleDetailPanel *panel);

    UPROPERTY()
    class UBundleDetailPanel *bunddetailPanel;
	UFUNCTION()
    void OnBundlesButtonClicked();
	
};
