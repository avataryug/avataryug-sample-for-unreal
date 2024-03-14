// Fill out your copyright notice in the Description page of Project Settings.

#include "OnBoardingAvatarButton.h"
#include "CommonModels.h"

void UOnBoardingAvatarButton::NativeConstruct()
{
  Super::NativeConstruct();

  AvatarButton->OnClicked.RemoveDynamic(this, &UOnBoardingAvatarButton::OnAvatarButtonClick);
  AvatarButton->OnClicked.AddDynamic(this, &UOnBoardingAvatarButton::OnAvatarButtonClick);

  OnReceiveTexture.BindUFunction(this, "OnLoadImage");

  if (APIEvents == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
    APIEvents = Cast<AAPIEvents>(FoundActor);
    if (APIEvents == nullptr)
    {
      APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
    }
  }
}

void UOnBoardingAvatarButton::SetButtonData(int index)
{
  DataIndex = index;
}
void UOnBoardingAvatarButton::SetNewButtonData(int index, FString url)
{
  DataIndex = index;
  ULoadTextureFromURL::LoadTexture(url, OnReceiveTexture);
}
void UOnBoardingAvatarButton::OnAvatarButtonClick()
{
  UE_LOG(LogTemp, Display, TEXT("ONCLICK BUTTON Value------>>%d"), DataIndex);
  //  APIEvents->OnChangeFlipbookIndex.Broadcast(DataIndex);
  // APIEvents->OnOnBoardingClickIndex.Broadcast(DataIndex);
}

void UOnBoardingAvatarButton::OnLoadImage(UTexture2D *textures)
{
  AvatarImage->SetBrushFromTexture(textures, false);
}
