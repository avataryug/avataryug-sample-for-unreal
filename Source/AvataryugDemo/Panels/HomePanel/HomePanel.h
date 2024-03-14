// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ContentWidget.h"
#include "../SettingPanel/SettingPanel.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "../../DataHolders/DataHolder.h"
#include "../CoinsPanel/CoinHeaderPanel.h"
#include "../../Panels/CustomizeAvatarPanels/CustomizeFullAvatarPanel.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/CommonFunction.h"
#include "Components/Button.h"
#include "HomePanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UHomePanel : public UUserWidget
{
    GENERATED_BODY()
protected:
    void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *HP_SettingButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *InventoryButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *ContainersButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *BundlesButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *CustomizeAvatarButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *LobbyCoinButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *RewardButton;

    UFUNCTION()
    void OnClickLobbyCoinButton();

    UFUNCTION()
    void LoadCustomizeAvatars();

    UFUNCTION()
    void OnClickSettingButton();

public:
    void LoadHomePanelDetail();

    AAPIEvents *APIEvents;

    UFUNCTION()
    void OnClickInventoryButton();

    UFUNCTION()
    void OnClickContainesButton();

    UFUNCTION()
    void OnClickRewardButton();

    UFUNCTION()
    void OnClickBundlesButton();

    UFUNCTION()
    void OnClickCustomizeAvatarButton();

    UPROPERTY()
    AUserDetailHolder *UserDetailHolder;

    UPROPERTY()
    AAvatarHandler *AvatarHandler;

    ADataHolder *DataHolder;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UCoinHeaderPanel *CoinHeaderPanel;

    UPROPERTY(BlueprintAssignable, Category = "Props")
    FOnPropProcessed OnPropProcess;

    UPROPERTY()
    ACurrentAvatarChanges *CurrentAvatarChangesHolder;

    void LoadCurrentAvatarData(TFunction<void()> oncomplete);

    	UPROPERTY()
	ACommonFunction *CommonFunctionHolder;
   	UPROPERTY()
	UCustomizeFullAvatarPanel *CustomizeFullAvatarPanel;
};
