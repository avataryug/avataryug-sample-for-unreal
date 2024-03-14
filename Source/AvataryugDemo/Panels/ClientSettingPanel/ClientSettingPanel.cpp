// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSettingPanel.h"


void UClientSettingPanel::NativeConstruct()
{
    Super::NativeConstruct();
  
    if (DataHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADataHolder::StaticClass());
        DataHolder = Cast<ADataHolder>(FoundActor);
        if (DataHolder == nullptr)
        {
            DataHolder = GetWorld()->SpawnActor<ADataHolder>();
        }
    }
  if (APIEvents == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
    APIEvents = Cast<AAPIEvents>(FoundActor);
    if (APIEvents == nullptr)
    {
      APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
    }
    if(APIEvents)
    {
      APIEvents->OnScreenOrientation.AddDynamic(this,&UClientSettingPanel::ClientSettingOrientation);
    }
  }


  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
     if (AvatarHandler == nullptr)
    {
      AvatarHandler = GetWorld()->SpawnActor<AAvatarHandler>();
    }
  }

  
    AppButton->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickAppButton);
    AppButton->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickAppButton);

    GameButton->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickGameButton);
    GameButton->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickGameButton);

    MonitizeButton->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickMonitizeButton);
    MonitizeButton->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickMonitizeButton);

    NonMonitizeButton->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickNonMonitizeButton);
    NonMonitizeButton->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickNonMonitizeButton);
    
    OnBoarding1Button->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickOnBoarding1Button);
    OnBoarding1Button->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickOnBoarding1Button);
    
    OnBoarding2Button->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickOnBoarding2Button);
    OnBoarding2Button->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickOnBoarding2Button);

    OnBoarding3Button->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickOnBoarding3Button);
    OnBoarding3Button->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickOnBoarding3Button);

    NextButton->OnClicked.RemoveDynamic(this, &UClientSettingPanel::OnClickNextButton);
    NextButton->OnClicked.AddDynamic(this, &UClientSettingPanel::OnClickNextButton);

    OnBoarding1Button->SetVisibility(ESlateVisibility::Collapsed);
    AvatarHandler->typeOfOnBoarding = EOnBoarding::OnBoarding2;
}

void UClientSettingPanel::OnClickNextButton()
{
  switch (AvatarHandler->typeOfOnBoarding)
  {
    case EOnBoarding::OnBoarding1:
      // OnBoarding1Button->SetBackgroundColor(NewBackgroundColor);
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
    break;
    case EOnBoarding::OnBoarding2:
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING2, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
      UE_LOG(LogTemp,Display,TEXT("OnBoarding2-->>"));
    break;
    case EOnBoarding::OnBoarding3:
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING3, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
      UE_LOG(LogTemp,Display,TEXT("OnBoarding3-->>"));
    break;
  }

}

void UClientSettingPanel::LoadClientSettingPanelData()
{
    FLinearColor NewBackgroundColor = FLinearColor(0.108127f, 0.858824f, 0.331202f);
    AppButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    GameButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    MonitizeButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    NonMonitizeButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    OnBoarding1Button->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    OnBoarding2Button->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    OnBoarding3Button->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f));
    
    switch (AvatarHandler->typeOfPlatform)
    {
        case EAppType::APP:
            AppButton->SetBackgroundColor(NewBackgroundColor);
        break;
        case EAppType::GAME:
            GameButton->SetBackgroundColor(NewBackgroundColor);
        break;
    }
    switch (AvatarHandler->TypeOfMontization)
    {
        case EMonitizeType::Monitize:
            MonitizeButton->SetBackgroundColor(NewBackgroundColor);
        break;
        case EMonitizeType::NonMonitize:
            NonMonitizeButton->SetBackgroundColor(NewBackgroundColor);
        break;
    }
    switch (AvatarHandler->typeOfOnBoarding)
    {
        case EOnBoarding::OnBoarding1:
            OnBoarding1Button->SetBackgroundColor(NewBackgroundColor);
        break;
        case EOnBoarding::OnBoarding2:
            OnBoarding2Button->SetBackgroundColor(NewBackgroundColor);
        break;
        case EOnBoarding::OnBoarding3:
            OnBoarding3Button->SetBackgroundColor(NewBackgroundColor);
        break;
    }
}

void UClientSettingPanel::OnClickAppButton()
{
  AvatarHandler->typeOfPlatform = EAppType::APP;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickGameButton()
{
  AvatarHandler->typeOfPlatform = EAppType::GAME;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickMonitizeButton()
{
  AvatarHandler->TypeOfMontization = EMonitizeType::Monitize;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickNonMonitizeButton()
{
  AvatarHandler->TypeOfMontization = EMonitizeType::NonMonitize;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickOnBoarding1Button()
{
  AvatarHandler->typeOfOnBoarding = EOnBoarding::OnBoarding1;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickOnBoarding2Button()
{
  AvatarHandler->typeOfOnBoarding = EOnBoarding::OnBoarding2;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::OnClickOnBoarding3Button()
{
  AvatarHandler->typeOfOnBoarding = EOnBoarding::OnBoarding3;
  LoadClientSettingPanelData();
}

void UClientSettingPanel::ClientSettingOrientation(bool isLandscape)
{
  if(isLandscape)
  {
    //  UButtonSlot *GameButtonSlot = Cast<UButtonSlot>(GameButtonVerticalBox->Slot);

    // GameButtonSlot->SetPadding(0,10,0,10);
    UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(GameButtonImage->Slot);
    VerticalBoxSlot->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));

    UVerticalBoxSlot* AppButtonImageBoxSlot = Cast<UVerticalBoxSlot>(AppButtonImage->Slot);
    AppButtonImageBoxSlot->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));

    UVerticalBoxSlot* MonitizeButtonImageBoxSlot = Cast<UVerticalBoxSlot>(MonitizeButtonImage->Slot);
    MonitizeButtonImageBoxSlot->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));
  
    UVerticalBoxSlot* NonMonitizeButtonSlot = Cast<UVerticalBoxSlot>(NonMonitizeButtonImage->Slot);
    NonMonitizeButtonSlot->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));
  }
  else
  {
    UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(GameButtonImage->Slot);
    VerticalBoxSlot->SetPadding(FMargin(40.0f,40.0f,40.0f,40.0f));

    UVerticalBoxSlot* AppButtonImageBoxSlot = Cast<UVerticalBoxSlot>(AppButtonImage->Slot);
    AppButtonImageBoxSlot->SetPadding(FMargin(40.0f,40.0f,40.0f,40.0f));

    UVerticalBoxSlot* MonitizeButtonImageBoxSlot = Cast<UVerticalBoxSlot>(MonitizeButtonImage->Slot);
    MonitizeButtonImageBoxSlot->SetPadding(FMargin(40.0f,40.0f,40.0f,40.0f));
  
    UVerticalBoxSlot* NonMonitizeButtonSlot = Cast<UVerticalBoxSlot>(NonMonitizeButtonImage->Slot);
    NonMonitizeButtonSlot->SetPadding(FMargin(40.0f,40.0f,40.0f,40.0f));
  }
}