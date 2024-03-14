// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Utilitys/APIEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ImageUtils.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "Components/Image.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "Http.h"
#include "OnBoardingAvatarButton.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingAvatarButton : public UUserWidget
{
  GENERATED_BODY()
protected:
  UPROPERTY(meta = (BindWidget))
	class UButton *AvatarButton;

  UPROPERTY(meta = (BindWidget))
  class UImage *AvatarImage;

	void NativeConstruct() override;
public:
  UFUNCTION()
	void SetButtonData(int index);

  UFUNCTION()
  void SetNewButtonData(int index, FString url);

    UFUNCTION()
    void OnAvatarButtonClick();

    int DataIndex;
	UFUNCTION()
  void OnLoadImage(UTexture2D *textures);
  AAPIEvents *APIEvents;

  UPROPERTY()
  FOnReceiveTexture OnReceiveTexture;
	
};
