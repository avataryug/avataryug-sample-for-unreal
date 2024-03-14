// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "../../DataHolders/UndoHandler.h"
#include "Components/Button.h"
#include "ColorPicker/ColorPickerWidget.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "ResetAvatarPanel.h"
#include "CategoryButton.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/CheckBox.h"
#include "JsonObjectConverter.h"
#include "Components/OverlaySlot.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../Utilitys/APIEvents.h"
#include "CommonModels.h"
#include "../../Panels/CoinsPanel/CoinHeaderPanel.h"
#include "EconomyAPI/EconomyRequest.h"
#include "CustomizeData.h"
#include "PropItemGridPanel.h"
#include "EconomyAPI/EconomyModel.h"
#include "../../DataHolders/CommonFunction.h"
#include "Components/ListView.h"
#include "CustomizeHeadAvatarPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UCustomizeHeadAvatarPanel : public UUserWidget
{
    GENERATED_BODY()
protected:
    void NativeConstruct() override;

    // Top Panel
    UPROPERTY(meta = (BindWidget))
    class UButton *BackButton;

    /// @brief
    UPROPERTY(meta = (BindWidget))
    class UButton *HeadCustomizeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ExpressionClipButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *FullBodyModification_Button;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox *HeadDarkModeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *InfoButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *UndoButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ResetButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *BuySaveButton;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *SortPanel;

    UPROPERTY(meta = (BindWidget))
    class UButton *SortButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *hightolowButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *lowtohighButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *CancelSortButton;

    UPROPERTY(meta = (BindWidget))
    class UListView *PropItemListView;

    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox *HeadResetBuyHoziBox;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *BuyTextHeadPanel;

    UPROPERTY(meta = (BindWidget))
    class UListView *SubCatListView;

    UPROPERTY(meta = (BindWidget))
    class USizeBox *SubHeadCategorySizeBox;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *FaceButtonsTopPanel;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *FacePropBottomPanel;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *FaceCoinTop_Panel;

      UPROPERTY(meta = (BindWidget))
  class USizeBox *SortButtonBox;

public:
    UPROPERTY(EditAnywhere)
    class UCategoryButton *InventoryButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *SkinToneButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *HairButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EyebrowButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EyeballButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *LipsButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *FacialhairButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *FaceShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *NoseShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EyebrowsShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EyeShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *LipShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EarShapeButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *HeadwearButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *EyewearButton;
    UPROPERTY(EditAnywhere)
    class UCategoryButton *AccessoriesButton;

    UPROPERTY()
    TArray<UCategoryButton *> MainCategoryButton;
    UPROPERTY(meta = (BindWidget))
    class UImage *SwiftRounded_Left;

    UPROPERTY(meta = (BindWidget))
    class UImage *SwiftRounded_Center;

    UPROPERTY(meta = (BindWidget))
    class UImage *SwiftRounded_Right;

public:
    UFUNCTION()
    void OnClickBackButton();

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UColorPickerWidget *ColorPickerWidgetPanel;

    TArray<FEconomyItems> currentSelectedItems;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UCoinHeaderPanel *CoinHeaderPanel;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UResetAvatarPanel *ResetHeadAvatarPanel;

    UFUNCTION()
    void LoadCustomizeAvatarHeadPanelData();

    FTimerHandle TimerHandle;

    UFUNCTION()
    void OnClickHeadCustomizeButton();

    UFUNCTION()
    void OnClickExpressionClipButton();

    UFUNCTION()
    void OnHeadDarkModeToggleStateChanged(bool bNewState);

    UFUNCTION()
    void OnClickFullBodyCustomizeButton();

    UFUNCTION()
    void OnClickInfoButton();

    UFUNCTION()
    void OnClickUndoButton();

    UFUNCTION()
    void OnClickResetButton();

    UFUNCTION()
    void OnClickBuySaveButton();

    UFUNCTION()
    void OnClickSortButton();

    UFUNCTION()
    void SortHighToLow();

    UFUNCTION()
    void SortLowToHigh();

    UFUNCTION()
    void SortCancelButton();

    UFUNCTION()
    void UpdateHeadBuyUI(bool isUpdate);

    UPROPERTY()
    FString CurrentSelectedMainCategory;

    UPROPERTY()
    FString CurrentSelectedSubCategory;

    TArray<FString> MainCategorys = {"Inventory", "SkinTone", "Hair", "Eyebrow", "Eyeball", "Lips", "Facialhair",
                                     "FaceShape", "NoseShape", "EyebrowShape", "EyeShape", "LipShape", "EarShape", "Headwear", "Eyewear", "Accessories"};

    UFUNCTION()
    void OnClickMainCategoryButton(FString category);

    FOnClickMainCategory OnClickMainCategory;

    AEconomyItemHolder *EconomyItemHolder;

    FOnGetEconomyItemsResult OnGetEconomyItemsResult;

    UFUNCTION()
    void OnReceiveEconomyItems(FGetEconomyItemsResult result);

    FOnApiException OnGetEconomyItemsError;
    UFUNCTION()
    void OnReceiveEconomyItemsError(FApiException result);
    UFUNCTION()
    void ShowPropItems(FString categtory);

    AAPIEvents *APIEvents;
    // AAvatarLoader *AvatarLoader;
    FOnClickSubCategory OnClickSubCategory;
    ADataHolder *DataHolder;

    UPROPERTY()
    AAvatarHandler *AvatarHandler;

    UPROPERTY()
    ACurrentAvatarChanges *CurrentAvatarChanges;

    UPROPERTY()
    ACommonFunction *CommonFunctionHolder;

    UFUNCTION()
    void OnClickSubCategoryButton(FString category);
    AUndoHandler *UndoHandler;
    UFUNCTION()
    void BuildModelButton();
    UFUNCTION()
    void OnPropClickCallback(bool isSelect);
    UFUNCTION()
    void ShowInventoryPropItems(FString categtory);
    UFUNCTION()
    void FaceScreenOrientation(bool isLandscape);
    AUserInventoryHolder *UserInventoryHolder;

    UPROPERTY(meta = (BindWidget))
    class UButton *FixedColorButton;
    UPROPERTY(meta = (BindWidget))
    class UButton *CustomColorButton;
    UPROPERTY(meta = (BindWidget))
    class UButton *OKButton;

    UPROPERTY(meta = (BindWidget))
    class USizeBox *ColorButonPanel;
    UFUNCTION()
    void OnClickFixedColorButton();
    UFUNCTION()
    void OnClickCustomColorButton();
    UFUNCTION()
    void OnClickOkButton();

    UFUNCTION()
    void GetReference();

    UFUNCTION()
    void SubscribeEvents();

    UFUNCTION()
    void SetButtonEvents();

    UFUNCTION()
    void OnItemSelected();

    UFUNCTION()
    void UpdateBuySaveButtonAfterChanges();
    UPROPERTY()
    AUserDetailHolder *UserDetailHolder;
    AAllGraphicsHolder *AllGraphicsHolder;
    UFUNCTION()
    void UpdateUIAfterPurchase();
};
