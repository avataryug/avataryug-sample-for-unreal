// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "EconomyAPI/EconomyModel.h"
#include "EconomyAPI/EconomyHandler.h"
#include "Components/ListView.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ContainersData.h"
#include "Components/TextBlock.h"
#include "ContainerDetailButton.generated.h"



UCLASS()
class UContainerDetailListData : public UObject {
	GENERATED_BODY()
  public:
	FContainerBase data;
	

};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UContainerDetailButton : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
	
	protected:
	void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	public:
	UPROPERTY(meta = (BindWidget))
	class UButton *ContainerDetailItemButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ContainerDetailItemNameText;

	TArray<FGetEconomyItemsByIDResultData> economyItemsList;

	UFUNCTION()
	void OnContainetDetailButtonClick();
	UFUNCTION()
	void SetBundlesDetail(FContainerBase data);
	UFUNCTION()
	void SetContainerDetail(FContainerBase data);
	UFUNCTION()
	void SetCurrenciesDetail(FContainerBase data);
	UFUNCTION()
	void SetDroptableDetail(FContainerBase data);
	UFUNCTION()
	void SetItemDetail(FContainerBase data);

	FOnGetEconomyItemsByIDResult OnGetEconomyItemsByIDResult;

	UFUNCTION()
	void GetEconomyItemsByIDReply(FGetEconomyItemsByIDResult result);

	FOnApiException OnGetEconomyItemsByIDError;

	UFUNCTION()
	void GetEconomyItemsByIDApiError(FApiException error);

// ===============Bundles===========

	FOnGetEconomyBundleByIDResult OnGetEconomyBundleByIDResult;

	UFUNCTION()
	void GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result);

	FOnApiException OnGetEconomyBundleByIDError;

	UFUNCTION()
	void GetEconomyBundleByIDApiError(FApiException error);

// ===============Containers===========

FOnGetEconomyContainerByIDResult  OnGetEconomyContainerByIDResult;

UFUNCTION()
void GetEconomyContainerByIDReply(FGetEconomyContainerByIDResult result);

FOnApiException OnGetEconomyContainerByIDError;

UFUNCTION()
void GetEconomyContainerByIDApiError(FApiException error);

	AAPIEvents *APIEvents;

};
