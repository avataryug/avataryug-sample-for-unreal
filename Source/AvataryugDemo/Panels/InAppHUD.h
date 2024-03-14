// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <components/Button.h>
#include <components/TextBlock.h>
#include "Components/WidgetComponent.h"
#include "Components/PanelWidget.h"
#include "NotificationPanel/NotificationPanel.h"
#include "AuthenticationPanels/AuthenticationPanel.h"
#include "LoadingPanel/LoadingPanel.h"
#include "NotificationPanel/ErrorNotificationPanel.h"
#include "../Utilitys/APIEvents.h"
#include "HomePanel/HomePanel.h"
#include "StorePanel/StorePanel.h"
#include "OnBoardingPanel/OnBoardingPanel.h"
#include "OnBoardingPanel/OnBoardingTwoPanel.h"
#include "OnBoardingPanel/OnBoardingThree.h"
#include "ContainersPanel/ContainersPanel.h"
#include "ContainersPanel/ContainerDetailPanel.h"
#include "SettingPanel/SettingPanel.h"
#include "InventoryPanel/InventoryPanel.h"
#include "CustomizeAvatarPanels/CustomizeFullAvatarPanel.h"
#include "CustomizeAvatarPanels/DetailPanel.h"
#include "BundlesPanel/BundlesPanel.h"
#include "BuyItemPanel/BuyItemPanel.h"
#include "AdsPanel/AdsPanel.h"
#include "GameEnums.h"
#include "ClientSettingPanel/ClientSettingPanel.h"
#include "CustomizeAvatarPanels/CustomizeHeadAvatarPanel.h"
#include "CustomizeAvatarPanels/ClipAndExpressionPanel.h"
#include "CustomizeAvatarPanels/CustomizeBlendshapePanel.h"
#include "CustomizeAvatarPanels/AvatarGeneratedPopup.h"
#include "InAppHUD.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API AInAppHUD : public AHUD
{
	GENERATED_BODY()
public:
	AInAppHUD();

	void DrawHUD() override;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void ShowOnBoardingPannel();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuthenticationPanel> BP_AuthenticationPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UAuthenticationPanel *AuthenticationPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadingPanel> BP_LoadingPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	ULoadingPanel *LoadingPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNotificationPanel> BP_NotificationPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UNotificationPanel *NotificationPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UErrorNotificationPanel> BP_ErrorNotificationPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UErrorNotificationPanel *ErrorNotificationPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHomePanel> BP_HomePanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UHomePanel *HomePanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStorePanel> BP_StorePanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UStorePanel *StorePanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOnBoardingPanel> BP_OnBoardingPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UOnBoardingPanel *OnBoardingPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOnBoardingTwoPanel> BP_OnBoardingTwoPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UOnBoardingTwoPanel *OnBoardingTwoPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOnBoardingThree> BP_OnBoardingThreePanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UOnBoardingThree *OnBoardingThreePanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USettingPanel> BP_SettingPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	USettingPanel *SettingPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAdsPanel> BP_AdsPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UAdsPanel *AdsPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryPanel> BP_InventoryPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UInventoryPanel *InventoryPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBundlesPanel> BP_BundlesPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UBundlesPanel *BundlesPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UContainersPanel> BP_ContainersPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UContainersPanel *ContainersPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UContainerDetailPanel> BP_ContainerDetailPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UContainerDetailPanel *ContainerDetailPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomizeFullAvatarPanel> BP_CustomizeFullAvatarPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UCustomizeFullAvatarPanel *CustomizeFullAvatarPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomizeHeadAvatarPanel> BP_CustomizeHeadAvatarPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UCustomizeHeadAvatarPanel *CustomizeHeadAvatarPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UClipAndExpressionPanel> BP_ClipAndExpressionPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UClipAndExpressionPanel *ClipAndExpressionPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomizeBlendshapePanel> WBP_CustomizeBlendshapePanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UCustomizeBlendshapePanel *CustomizeBlendshapePanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UClientSettingPanel> WBP_ClientSettingPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UClientSettingPanel *ClientSettingPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDetailPanel> WBP_DetailPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UDetailPanel *DetailPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuyItemPanel> WBP_BuyItemPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UBuyItemPanel *BuyItemPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAvatarGeneratedPopup> WBP_AvatarGeneratedPopup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UAvatarGeneratedPopup *AvatarGeneratedPopup;

	AAPIEvents *APIEvents;
	UFUNCTION()
	void ShowLoadingPanel(bool show);

	UFUNCTION()
	void ShowNotificationPanel(FString title, FString message);

	UFUNCTION()
	void ShowErrorNotificationPanel(FString title, FString message);

	UFUNCTION()
	void ShowHomePanel(bool show);

	UFUNCTION()
	void ShowSettingPanel(bool show);

	UFUNCTION()
	void ShowOnboardingPanel();

	UFUNCTION()
	void ShowPanel(EUIPanels panels, bool Loaddata);

	UFUNCTION()
	void HidePanel(EUIPanels panels);
	UFUNCTION()
	void ShowAvatarGeneratedPanel(FString meshurl, FString imageurl);
};
