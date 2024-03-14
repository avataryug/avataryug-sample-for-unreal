// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ContainersData.generated.h"

USTRUCT(BlueprintType)
struct FCurrencyPrise
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    bool Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString UserID;
};

USTRUCT(BlueprintType)
struct FVirtualCurrencyReward
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FCurrencyPrise> currencyRewards;
};

USTRUCT(BlueprintType)
struct FContainerBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString UserID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString containerType;
};

USTRUCT(BlueprintType)
struct FContainerBundleContents
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FContainerBase> Bundles ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FContainerBase> Container ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FContainerBase> Currencies ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FContainerBase> Droptable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FContainerBase> Items ;
};

USTRUCT(BlueprintType)
struct FContainerSetting
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ContainerSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString LockedID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString LockedItemID;
};

USTRUCT(BlueprintType)
struct FContainerDataClass
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ContainerCategory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ContainerImageUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int IsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int IsLimitedEdition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int LimitedEditionIntialCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Entitlement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FContainerSetting containerSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FContainerBundleContents containerContents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FVirtualCurrencyReward VirtualCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int RealCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString CustomMetaData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ID;
};


UCLASS()
class UContainerListData : public UObject {
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	TArray<FContainerDataClass> Containers;
	UPROPERTY()
	class UContainerDetailPanel *panel;

};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UContainersData : public UObject
{
	GENERATED_BODY()
	
};
