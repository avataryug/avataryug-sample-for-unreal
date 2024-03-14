// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ContainersData.h"
#include "ContainerDetailPanel.h"
#include "Components/TextBlock.h"
#include "ContainerButton.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UContainerButton : public UUserWidget
{
    GENERATED_BODY()

protected:
    void NativeConstruct() override;

public:
    UPROPERTY(meta = (BindWidget))
    class UButton *CIB_ContainerItemButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *CIB_priceText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *ContainerNameText;

    UFUNCTION()
    void SetButton(FContainerDataClass data, UContainerDetailPanel *panel);

    UPROPERTY()
    FContainerDataClass currentData;

    UPROPERTY()
    class UContainerDetailPanel *contdetailPanel;

    UFUNCTION()
    void OnContainerButtonClicked();


};
