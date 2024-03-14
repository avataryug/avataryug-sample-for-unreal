// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/LocalDataFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "CustomizeBlendshapePanel.generated.h"

USTRUCT(BlueprintType)
struct FChangedShape
{
	GENERATED_USTRUCT_BODY()
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    float value;
	
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString slideKey;
};

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UCustomizeBlendshapePanel : public UUserWidget
{
    GENERATED_BODY()
protected:
    void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *BackButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ProceedButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *FrontHeadButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *SideHeadButton;

    UPROPERTY(meta = (BindWidget))
    class USlider *HorizontalSlider;

    UPROPERTY(meta = (BindWidget))
    class USlider *VerticalSlider;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox *ShowHideModels;

    UFUNCTION()
    void OnShowHideModels(bool bNewValue);

    UFUNCTION()
    void OnHorizontalValueChange(float value);

    UFUNCTION()
    void OnVerticalValueChange(float value);

    UFUNCTION()
    void OnBackButtonClick();

    UFUNCTION()
    void OnProcessButtonClick();

    UFUNCTION()
    void OnFrontHeadButtonClick();

    UFUNCTION()
    void OnSideHeadButtonClick();

    AAPIEvents *APIEvents;

    // UPROPERTY()
    // AAvatarLoader *AvatarLoader;

    UPROPERTY()
    AAvatarHandler *AvatarHandler;

public:
    FString Category;
    UFUNCTION()
    void LoadBlendPanel();

    UFUNCTION()
    void OnclickBlendshapePoint(FString name);

    FString VerticalKeyValue;

    FString HorizontalKeyValue;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    // FDelegateOnBlendshapePoint OnBlendshapePoint;
    TArray<FChangedShape> changedShape;

    void AddShape(float value ,FString key);
};
