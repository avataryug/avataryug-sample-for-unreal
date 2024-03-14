// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorPickerButton.h"

void UColorPickerButton::NativeConstruct()
{
  Super::NativeConstruct();

  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
    // AvatarHandler->SetActorLabel(FString("AvatarHandler"));
  }

  ColorButton->OnClicked.RemoveDynamic(this, &UColorPickerButton::OnClickColorButton);
  ColorButton->OnClicked.AddDynamic(this, &UColorPickerButton::OnClickColorButton);
}

void UColorPickerButton::OnClickColorButton()
{
  // AvatarLoader->SetBodyPartColor(OutColor, Category);
  AvatarHandler->ForCustomizeAvatar->SetBodyPartColor(OutColor, Category);
}

void UColorPickerButton::SetButton(FString cat, FString color)
{
  Category = cat;
  UAvataryugFunctionLibrary::HexToLinearColor(color, OutColor);
  ColorImage->SetBrushTintColor(FSlateColor(OutColor));
}