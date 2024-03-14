// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ErrorNotificationPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UErrorNotificationPanel : public UUserWidget
{
	GENERATED_BODY()

	protected:
	void NativeConstruct() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ErrorCodeText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ErrorLogText;

	UPROPERTY(meta = (BindWidget))
	class UButton *OkButton;


	UFUNCTION()
	void ShowErrorNotification(FString code, FString message);

	UFUNCTION()
	void OnOkButtonClick();	
};
