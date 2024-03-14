// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LoadingPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API ULoadingPanel : public UUserWidget
{
  GENERATED_BODY()
  protected:
    void NativeConstruct() override;
    
    UPROPERTY(meta = (BindWidget))
    class UButton *LoadingButton;

    UFUNCTION()
    void OnLoadingClick();
};
