// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContainersData.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ListView.h"
#include "ContainerDetailPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UContainerDetailPanel : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UListView *ContainerDetailItemListView;

	UPROPERTY(meta = (BindWidget))
	class UButton *CDP_BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CDP_BuyButton;

	UFUNCTION()
	void LoadDetailContainers(FContainerDataClass itemData);

	UPROPERTY()
	FContainerDataClass container;
	UPROPERTY()
	TArray<FContainerBundleContents> containerContents;
	TArray<FContainerBase> containerbases;
	FVirtualCurrencyReward virtualCurrrency;

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	UPROPERTY()
	AUserInventoryHolder *UserInventoryHolder;

	UFUNCTION()
	void OnClickCDP_BackButton();

	UFUNCTION()
	void OnClickCDP_BuyButton();

	AAPIEvents *APIEvents;

	bool IsContainerEmpty(const FContainerDataClass &container);

	bool IsContainerSettingEmpty(const FContainerSetting &setting);

	bool IsContainerBundleContentsEmpty(const FContainerBundleContents &cont);

	bool IsVirtualCurrencyRewardEmpty(const FVirtualCurrencyReward &reward);

	UPROPERTY()
	FOnPurchaseInstanceResult OnPurchaseInstanceResult;
	UFUNCTION()
	void PurchaseInstanceReply(FString result);
	UPROPERTY()
	FOnApiException OnPurchaseInstanceError;
	UFUNCTION()
	void PurchaseError(FApiException error);

	UPROPERTY()
	FOnGetUserInventoryResult OnGetUserInventoryResult;
	UFUNCTION()
	void UserInventoryReply(FGetUserInventoryResult result);
	FOnApiException OnInventoryApiError;
	UFUNCTION()
	void InventoryApiError(FApiException error);
};
