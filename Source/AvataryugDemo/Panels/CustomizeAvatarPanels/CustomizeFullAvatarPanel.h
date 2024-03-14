// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResetAvatarPanel.h"
#include "CommonModels.h"
#include "EconomyAPI/EconomyRequest.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "Components/Button.h"
#include "../../DataHolders/UndoHandler.h"
#include "Components/HorizontalBox.h"
#include "CustomizeData.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "PropItemGridPanel.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../Panels/CoinsPanel/CoinHeaderPanel.h"
#include "Components/CheckBox.h"
#include "EconomyAPI/EconomyModel.h"
#include "Components/ListView.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/CommonFunction.h"
#include "CustomizeFullAvatarPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UCustomizeFullAvatarPanel : public UUserWidget
{
  GENERATED_BODY()
protected:
  void NativeConstruct() override;
  // Called when the game starts or when spawned

  // Top Panel
  UPROPERTY(meta = (BindWidget))
  class UButton *BackButton;

  /// @brief
  UPROPERTY(meta = (BindWidget))
  class UButton *HeadCustomizeButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *ExpressionClipButton;

  /// @brief
  UPROPERTY(meta = (BindWidget))
  class UButton *ZoomButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *ZoomOutButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *InfoButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *UndoButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *ResetButton;

  UPROPERTY(meta = (BindWidget))
  class UButton *BuySaveButton;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *CustomizeFullBodyPanel;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *FullBodyButtonsTopPanel;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *FullBodyPropBottomPanel;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *FullBodyCoinTop_Panel;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *ZoomInPanel;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *SortPanel;
  ////
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
  class UHorizontalBox *ResetBuyHorizontalBox;

  UPROPERTY(meta = (BindWidget))
  class USizeBox *SubCategorySizeBox;

  UPROPERTY(meta = (BindWidget))
  class UTextBlock *BuyText;

  UPROPERTY(meta = (BindWidget))
  class USizeBox *SortButtonBox;
  

public:
  UPROPERTY(EditAnywhere)
  class UCategoryButton *AvatarButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *InventoryButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *TopButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *BottomButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *OutfitButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *HandwearButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *WristwearButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *FootwearButton;
  UPROPERTY(EditAnywhere)
  class UCategoryButton *TattooButton;
  UPROPERTY(EditAnywhere, meta = (BindWidget))
  UCoinHeaderPanel *CoinHeaderPanel;

  UPROPERTY(EditAnywhere, meta = (BindWidget))
  UResetAvatarPanel *ResetFullAvatarPanel;

  UPROPERTY(meta = (BindWidget))
  class UCheckBox *DarkModeToggle;

  UPROPERTY(meta = (BindWidget))
  class UListView *SubCatListView;

  UPROPERTY()
  TArray<UCategoryButton *> MainCategoryButton;

public:
  UFUNCTION()
  void OnClickBackButton();

  TArray<FEconomyItems> currentSelectedItems;

  UFUNCTION()
  void LoadCustomizeAvatarPanelData();

  FTimerHandle TimerHandle;

  UFUNCTION()
  void OnClickHeadCustomizeButton();

  UFUNCTION()
  void OnClickExpressionClipButton();

  UFUNCTION()
  void OnClickZoomButton();

  UFUNCTION()
  void OnClickZoomoutButton();

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
  void CloseSortPanel();

  UPROPERTY()
  FString CurrentSelectedMainCategory;

  UPROPERTY()
  FString CurrentSelectedSubCategory;

  TArray<FString> MainCategorys = {"Avatars", "Inventory", "Top", "Bottom", "Outfit", "Handwear", "Wristwear", "Footwear", "Tatto"};

  TArray<FString> TattooCategorys =
      {
          "LeftHandTattoo", "RightHandTattoo", "LeftFootTattoo", "RightFootTattoo", "FrontLeftLegTattoo",
          "FrontRightLegTattoo", "LeftArmTattoo", "RightArmTattoo", "BackBodyTattoo", "FrontBodyTattoo", "BackRightLegTattoo",
          "BackLeftLegTattoo", "HeadTattoo"};

  TArray<FString> InventoryCategory = {
      /* "Avatars", "All",*/ "Top", "Bottom", "Outfit", "Footwear", "Handwear", "Wristwear", "LeftHandTattoo", "RightHandTattoo",
      "LeftArmTattoo", "RightArmTattoo", "LeftFootTattoo", "RightFootTattoo", "FrontLeftLegTattoo", "FrontRightLegTattoo",
      "BackBodyTattoo", "BackLeftLegTattoo", "BackRightLegTattoo", "SkinTone", "HeadTattoo"};

  UFUNCTION()
  void OnClickMainCategoryButton(FString category);

  FOnClickMainCategory OnClickMainCategory;

  AEconomyItemHolder *EconomyItemHolder;

  UFUNCTION()
  void ShowPropItems(FString categtory);

  UFUNCTION()
  void ShowInventoryPropItems(FString categtory);
  UFUNCTION()
  void SortHightoLow();
  UFUNCTION()
  void SortLowToHigh();

  AAPIEvents *APIEvents;

  // AAvatarLoader *AvatarLoader;
  AUndoHandler *UndoHandler;
  FOnClickSubCategory OnClickSubCategory;
  ADataHolder *DataHolder;
  UPROPERTY()
  AAvatarHandler *AvatarHandler;
  UPROPERTY()
  AUserDetailHolder *UserDetailHolder;
  UFUNCTION()
  void OnClickSubCategoryButton(FString category);

  UFUNCTION()
  void OnPropClickCallback(bool isSelect);

  UFUNCTION()
  void BuildModelButton();
  UFUNCTION()
  void OnItemSelected();

  UFUNCTION()
  void OnDarkModeToggleStateChanged(bool bNewState);

  UFUNCTION()
  void FullBodyScreenOrientation(bool isLandscape);

  AUserInventoryHolder *UserInventoryHolder;

  UPROPERTY()
  ACommonFunction *CommonFunctionHolder;

  UFUNCTION()
  void GetReference();

  UFUNCTION()
  void SubscribeEvents();

  UFUNCTION()
  void SetButtonEvents();

  UFUNCTION()
  void SetInitialDetails();

  UFUNCTION()
  void UpdateBuySaveButtonAfterChanges();

  UFUNCTION()
  int GetGender(FString category);

  UFUNCTION()
  void UpdateUIAfterPurchase();

  ACurrentAvatarChanges *CurrentAvatarChanges;
  bool CustomExportCallback(const void *PropertyValue,
                            const FProperty *Property, FJsonValue &JsonValue);

  AAllGraphicsHolder *AllGraphicsHolder;
};
