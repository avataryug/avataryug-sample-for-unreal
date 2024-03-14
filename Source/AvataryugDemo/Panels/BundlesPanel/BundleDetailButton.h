// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "BundlesData.h"
#include "EconomyAPI/EconomyModel.h"
#include "EconomyAPI/EconomyHandler.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "../../Utilitys/APIEvents.h"
#include "BundleDetailButton.generated.h"



UCLASS()
class UBundlesDetailListData : public UObject {
	GENERATED_BODY()
  public:
	FContainerBase data;
	

};
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBundleDetailButton : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()


	protected:
	void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;


	public:
	UPROPERTY(meta = (BindWidget))
	class UButton *BDI_ItemButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *BDI_PriceText;

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

// ===============ITEMS===========

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

	AEconomyItemHolder *EconomyItemHolder;

	AAPIEvents *APIEvents;
	
};
