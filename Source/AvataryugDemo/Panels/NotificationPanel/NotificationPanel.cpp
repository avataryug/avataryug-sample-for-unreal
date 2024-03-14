// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationPanel.h"

void UNotificationPanel::NativeConstruct()
{
    Super::NativeConstruct();
    
    OkButton->OnClicked.RemoveDynamic(this, &UNotificationPanel::OnOkButtonClick);
    OkButton->OnClicked.AddDynamic(this, &UNotificationPanel::OnOkButtonClick);
}

void UNotificationPanel::ShowNotification(FString title, FString message)
{
    TitleText->SetText(FText::FromString(title));
    MessageText->SetText(FText::FromString(message));
}

void UNotificationPanel::OnOkButtonClick()
{
   this->SetVisibility(ESlateVisibility::Hidden);
}

