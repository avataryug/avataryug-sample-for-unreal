// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "Blueprint/UserWidget.h"
#include "ResetAvatarPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UResetAvatarPanel : public UUserWidget
{
	GENERATED_BODY()

    protected:
      void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
    class UButton *ResetToCurrentButton;

	UPROPERTY(meta = (BindWidget))
    class UButton *ResetToDefaultButton;

	UPROPERTY(meta = (BindWidget))
    class UButton *CancelButton;

	UFUNCTION()
	void OnClickResetToCurrentButton();

	UFUNCTION()
    void OnClickResetToDefaultButton();

	UFUNCTION()
	void OnClickCancelButton();

	// UPROPERTY()
	// AAvatarLoader *AvatarLoader;

    UPROPERTY()
    AAvatarHandler *AvatarHandler;
};
