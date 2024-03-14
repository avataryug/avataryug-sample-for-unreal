// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetAvatarPanel.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UResetAvatarPanel::NativeConstruct()
{
    Super::NativeConstruct();

    // if (AvatarLoader == nullptr)
    // {
    //     AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarLoader::StaticClass());
    //     AvatarLoader = Cast<AAvatarLoader>(FoundActor);
    // }

    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
    }

    ResetToCurrentButton->OnClicked.RemoveDynamic(this, &UResetAvatarPanel::OnClickResetToCurrentButton);
    ResetToCurrentButton->OnClicked.AddDynamic(this, &UResetAvatarPanel::OnClickResetToCurrentButton);

    ResetToDefaultButton->OnClicked.RemoveDynamic(this, &UResetAvatarPanel::OnClickResetToDefaultButton);
    ResetToDefaultButton->OnClicked.AddDynamic(this, &UResetAvatarPanel::OnClickResetToDefaultButton);

    CancelButton->OnClicked.RemoveDynamic(this, &UResetAvatarPanel::OnClickCancelButton);
    CancelButton->OnClicked.AddDynamic(this, &UResetAvatarPanel::OnClickCancelButton);
}

void UResetAvatarPanel::OnClickResetToCurrentButton()
{
    // AvatarLoader->ResetToCurrentSelected();
    AvatarHandler->ForCustomizeAvatar->ResetToCurrentSelected();
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UResetAvatarPanel::OnClickResetToDefaultButton()
{
    AvatarHandler->ForCustomizeAvatar->ResetToDetaultModel();
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UResetAvatarPanel::OnClickCancelButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}