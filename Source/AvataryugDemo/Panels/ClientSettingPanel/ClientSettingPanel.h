// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../DataHolders/DataHolder.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/Image.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/VerticalBox.h"
#include "ClientSettingPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UClientSettingPanel : public UUserWidget
{
	GENERATED_BODY()
	protected:
    void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *AppButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *GameButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *MonitizeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *NonMonitizeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *OnBoarding1Button;

    UPROPERTY(meta = (BindWidget))
    class UButton *OnBoarding2Button;

    UPROPERTY(meta = (BindWidget))
    class UButton *OnBoarding3Button;
    
  	UPROPERTY(meta = (BindWidget))
  	class UButton *NextButton;

    // UPROPERTY(meta = (BindWidget))
	// class UVerticalBox *GameButtonVerticalBox;

    UPROPERTY(meta = (BindWidget))
    class UImage *GameButtonImage;

    UPROPERTY(meta = (BindWidget))
    class UImage *AppButtonImage;

    UPROPERTY(meta = (BindWidget))
    class UImage *MonitizeButtonImage;

    UPROPERTY(meta = (BindWidget))
    class UImage *NonMonitizeButtonImage;
  
	UFUNCTION()
    void OnClickAppButton();

    UFUNCTION()
    void OnClickGameButton();

    UFUNCTION()
    void OnClickMonitizeButton();

    UFUNCTION()
    void OnClickNonMonitizeButton();

    UFUNCTION()
    void OnClickOnBoarding1Button();

    UFUNCTION()
    void OnClickOnBoarding2Button();
    UFUNCTION()
    void OnClickOnBoarding3Button();
    UFUNCTION()
    void ClientSettingOrientation(bool isLandscape);
    UFUNCTION()
    void OnClickNextButton();

        
	UPROPERTY()
    ADataHolder *DataHolder;
    AAPIEvents *APIEvents;
    public:
	UFUNCTION()
        void LoadClientSettingPanelData();
          UPROPERTY()
    AAvatarHandler *AvatarHandler;
};
