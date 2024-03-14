// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/DataHolder.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "OnBoardingThree.h"
#include "Blueprint/UserWidget.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "ImageUtils.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "Http.h"
#include "Components/Button.h"
#include "OnBoardingThreeAvatarButton.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingThreeAvatarButton : public UUserWidget
{
  GENERATED_BODY()
  void NativeConstruct() override;

  UFUNCTION()
  void OnClickButton();

public:
  UPROPERTY(meta = (BindWidget))
  class UButton *ItemButton;

  UPROPERTY(meta = (BindWidget))
  class UImage *ItemImage;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *LoadingPanel;

  UPROPERTY(meta = (BindWidget))
  class UImage *SelectedImage;

  UPROPERTY()
  UOnBoardingThree * OnBoardingThree;

  FString Id;

  FGetAvatarPresetsResultDataInner onboardingThreeItem;
  void SetOnBoardThreeButton(UOnBoardingThree *OnBoardingThreeRef,FGetAvatarPresetsResultDataInner item, TFunction<void(FGetAvatarPresetsResultDataInner)> OnClickButton);
  TFunction<void(FGetAvatarPresetsResultDataInner)> OnClickButtons;
  UFUNCTION()
  void UpdateOnBoardThreeButtonData();

  UPROPERTY()
  AAllGraphicsHolder *AllGraphicsHolder;
UPROPERTY()
AAPIEvents *APIEvents;
UPROPERTY()
UOnBoardingThree *OnBoardingThreeRe;
UFUNCTION()
void OnSelectAvatarPreset(FGetAvatarPresetsResultDataInner data);
};
