// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameEnums.h"
#include "../DataHolders/EconomyItemHolder.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
// #include "ContainersPanel/ContainersData.h"
#include "APIEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowLoadingPanel, bool, show);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowSettingPanel, bool, show);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowHomePanel, bool, show);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateHeadPanelUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdatexpPanelUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateClipPanelUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateBuyButtonUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdatExpressBuyButtonUI, bool, update);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateHeadCatBuyButtonUI, bool, update);
DECLARE_DELEGATE(FMyCompletionDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoadNetworkModelDelegate, bool, sender, FEconomyItems, economyItems);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowNotiticationPanel, FString, title, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowErrorNotiticationPanel, FString, title, FString, message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChangeCamera, CameraPanels, panels);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHidePanel, EUIPanels, panel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowPanel, EUIPanels, panel, bool, loaddata);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetModelParentDelegate, EModelParent, panel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickMainCategory, FString, category);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChangeFlipbookIndex, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnClickIndex, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedIndex, int32, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPropClick, bool, isSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenOrientation, bool, orient);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnBlendshapePoint, FString, blendpointName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSelect);

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResetToDefaultDelegate, TFunction<void()>);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedContainerData, FContainerDataClass, data);
DECLARE_DELEGATE_OneParam(FOnResetToDefaultDelegate, TFunction<void()> EventCallback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnHorizontalInput, float, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnVerticalInput, float, value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowGeneratedAvatar, FString, meshurl, FString, imageurl);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateUiAfterPurchase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateUiAfterItemSelect);

UCLASS()
class AVATARYUGDEMO_API AAPIEvents : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAPIEvents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	FOnShowGeneratedAvatar OnShowGeneratedAvatar;
	UPROPERTY()
	FOnShowLoadingPanel OnShowLoadingPanel;

	UPROPERTY()
	FOnShowSettingPanel OnShowSettingPanel;

	UPROPERTY()
	FOnShowHomePanel OnShowHomePanel;

	UPROPERTY()
	FOnScreenOrientation OnScreenOrientation;

	UPROPERTY()
	FOnUpdateUI OnUpdateUI;

	UPROPERTY()
	FOnUpdateHeadPanelUI OnUpdateHeadUI;

	UPROPERTY()
	FOnUpdatexpPanelUI OnUpdatexpPanelUI;

	UPROPERTY()
	FOnUpdateClipPanelUI OnUpdateClipPanelUI;
	UPROPERTY()
	FOnUpdateBuyButtonUI OnUpdateBuyButtonUI;
	UPROPERTY()
	FOnUpdatExpressBuyButtonUI OnUpdatExpBuyButtonUI;

	UPROPERTY()
	FOnUpdateHeadCatBuyButtonUI OnUpdateHeadCatBuyButtonUI;

	UFUNCTION()
	void ShowLoading();
	UFUNCTION()
	void HideLoading();

	UFUNCTION()
	void UpdatesUI();
	UFUNCTION()
	void UpdatesHeadUI();
	UFUNCTION()
	void UpdatesExpUI();
	UFUNCTION()
	void UpdatesClipUI();
	UFUNCTION()
	void UpdatesBuyButtonUI();

	UPROPERTY()
	FOnShowNotiticationPanel OnShowNotiticationPanel;

	FOnResetToDefaultDelegate OnResetToDefault;

	UFUNCTION()
	void ShowNotification(FString title, FString message);

	UFUNCTION()
	void ShowSettingPanel();
	UFUNCTION()
	void HideSettingPanel();

	UFUNCTION()
	void ShowHomePanel();
	UFUNCTION()
	void HideHomePanel();

	UPROPERTY()
	FOnShowErrorNotiticationPanel OnShowErrorNotiticationPanel;
	UFUNCTION()
	void ShowErrorNotification(FString code, FString message);

	UPROPERTY()
	FOnShowPanel OnShowPanel;

	UPROPERTY()
	FOnHidePanel OnHidePanel;

	UPROPERTY()
	FSetModelParentDelegate OnSetModelParentDelegate;

	UPROPERTY()
	FLoadNetworkModelDelegate OnLoadNetworkModelDelegate;

	UFUNCTION()
	void LoadNetworkModelDelegate(bool sender, FEconomyItems e);

	UFUNCTION()
	void SetModelparent(EModelParent panels);

	UFUNCTION()
	void ShowPanel(EUIPanels panels, bool Loaddata);

	UFUNCTION()
	void HidePanel(EUIPanels panels);

	UFUNCTION()
	void ShowInventoryPanel(bool LoadData);

	UPROPERTY()
	FDelegateOnChangeFlipbookIndex OnChangeFlipbookIndex;

	FDelegateOnClickIndex OnOnBoardingClickIndex;

	UPROPERTY()
	FDelegateOnChangeCamera OnChangeCamera;
	UPROPERTY()
	FOnPropClick OnPropClick;
	UFUNCTION()
	void OnPropButtonClick(bool isSelect);

	FOnItemSelect OnItemSelect;

	UPROPERTY()
	FDelegateOnBlendshapePoint OnBlendshapePoint;

	UFUNCTION()
	void OnItemClick();

	UPROPERTY()
	FDelegateOnHorizontalInput OnHorizontalInput;

	UPROPERTY()
	FDelegateOnVerticalInput OnVerticalInput;
	//   UFUNCTION()
	//     void OnclickBlendshape(FString shapename);

	UFUNCTION()
	void SetResolution(bool isLandscape);

	bool isRotated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FString url;
	bool isMale = false;
	bool isCustomize = false;
	bool isDarkMode = false;
	//   UFUNCTION()
	//     void OnclickBlendshape(FString shapename);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FGetAvatarPresetsResultDataInner boardingSelectedThreeItem;

	FOnUpdateUiAfterPurchase OnUpdateUiAfterPurchase;
	UFUNCTION()
	void UpdateUiAfterPurchase();
	FOnUpdateUiAfterItemSelect OnUpdateUiAfterItemSelect;
	UFUNCTION()
	void UpdateUiAfterItemSelect();

	UFUNCTION()
	void ShowGeneratedAvatar(FString meshurl, FString imageurl);
};
