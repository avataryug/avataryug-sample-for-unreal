// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/Button.h"
#include "DefaultAPI/DefaultRequest.h"
#include "DefaultAPI/DefaultHandler.h"
#include "GameStructs.h"
#include "Components/CheckBox.h"
#include "../../DataHolders/CommonFunction.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "JsonObjectConverter.h"
#include "Components/ListView.h"
#include "../../DataHolders/DataHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "PropItemGridPanel.h"
#include "Components/SizeBox.h"
#include "../../Panels/CoinsPanel/CoinHeaderPanel.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "ClipAndExpressionPanel.generated.h"



/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UClipAndExpressionPanel : public UUserWidget
{
    GENERATED_BODY()
protected:
    void NativeConstruct() override;

    /// @brief
    UPROPERTY(meta = (BindWidget))
    class UButton *HeadCustomizeButton;

      UPROPERTY(EditAnywhere, meta = (BindWidget))
  UCoinHeaderPanel *CoinHeaderPanel;

    /// @brief
    UPROPERTY(meta = (BindWidget))
    class UButton *FullCustomizeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ExpressionButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ClipButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *BuySaveButton;

    UPROPERTY(meta = (BindWidget))
    class UListView *PropItemListView;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *ExpresssionButtonsTopPanel;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *ExpressionBottomPanel;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *ExpressionCoinTop_Panel;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *BuyText;

    UPROPERTY(meta = (BindWidget))
    class UImage *ExpSelectImage;
    
    UPROPERTY(meta = (BindWidget))
    class UImage *SelectClipImage;

    UPROPERTY(meta = (BindWidget))
    class USizeBox *ClipButtonSizeBox;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox *ExpDarkModeButton;

    UFUNCTION()
    void OnClickHeadCustomizeButton();

    UFUNCTION()
    void OnClickFullCustomizeButton();

    UPROPERTY()
    AAPIEvents *APIEvents;

    UPROPERTY()
    AAvatarHandler *AvatarHandler;



    UFUNCTION()
    void OnClickClipButton();

    UFUNCTION()
    void OnClickExpressionButton();

    UFUNCTION()
    void OnClickBuySaveButton();

    UFUNCTION()
    void OnDarkModeToggleStateChanged(bool bNewState);

    UFUNCTION()
    void ExpressionScreenOrientation(bool isLandscape);
    UFUNCTION()
    void UpdateClipExpPropUI(bool isUpdate);
    UFUNCTION()
    void UpdateClipPropUI(bool isUpdate);

    UPROPERTY()
    FOnGetClipsResponse GetClipsResponse;

    UFUNCTION()
    void OnGetClipsResponse(FGetClipsResponse result);

    UPROPERTY()
    FOnApiException GetClipsError;

    UFUNCTION()
    void OnGetClipsError(FApiException result);

    UPROPERTY()
    FOnGetExpressionsResponse GetExpressionsResponse;

    UFUNCTION()
    void OnGetExpressionsResponse(FGetExpressionsResponse result);

    UPROPERTY()
    FOnApiException GetExpressionsError;

    UFUNCTION()
    void OnGetExpressionsError(FApiException result);

    UFUNCTION()
    void OnItemSelected();

    UFUNCTION()
    void UpdateUIAfterPurchase();

    UFUNCTION()
    void UpdateBuySaveButtonAfterChanges();

      UFUNCTION()
    void BuildModelButton();
public:

    UFUNCTION()
    void LoadExpressionClipPanelData();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FExpression> expressionLists;

    UFUNCTION()
    void ShowExpressions();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FClip> clipLists;

    UFUNCTION()
    void ShowClips();
    
    ADataHolder *DataHolder;

    AUserInventoryHolder *UserInventoryHolder;
    
    ACurrentAvatarChanges *CurrentAvatarChanges;
    UPROPERTY()
    AUserDetailHolder *UserDetailHolder;
    
    UPROPERTY()
    ACommonFunction *CommonFunctionHolder;
    
    UPROPERTY()
    AAllGraphicsHolder *AllGraphicsHolder;
};
