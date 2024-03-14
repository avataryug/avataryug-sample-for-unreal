// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "NotificationPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UNotificationPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TitleText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *MessageText;

	UPROPERTY(meta = (BindWidget))
	class UButton *OkButton;

	UFUNCTION()
	void ShowNotification(FString title, FString message);

	UFUNCTION()
	void OnOkButtonClick();
};
