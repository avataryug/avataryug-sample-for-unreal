// Fill out your copyright notice in the Description page of Project Settings.


#include "ErrorNotificationPanel.h"

void UErrorNotificationPanel::NativeConstruct()
{
    Super::NativeConstruct();

    OkButton->OnClicked.RemoveDynamic(this, &UErrorNotificationPanel::OnOkButtonClick);
    OkButton->OnClicked.AddDynamic(this, &UErrorNotificationPanel::OnOkButtonClick);
}

void UErrorNotificationPanel::ShowErrorNotification(FString code, FString message)
{
    ErrorCodeText->SetText(FText::FromString(code));
    ErrorLogText->SetText(FText::FromString(message));
}

void UErrorNotificationPanel::OnOkButtonClick()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}