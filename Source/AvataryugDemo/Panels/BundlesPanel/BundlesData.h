// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ContainersPanel/ContainersData.h"
#include "BundlesData.generated.h"

USTRUCT(BlueprintType)
struct FEntitlements
{
	GENERATED_USTRUCT_BODY()

   	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ByCount;
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ByTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString TimeData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Type;
};
USTRUCT(BlueprintType)
struct FEconomyBundle
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString BundleCategory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int RealCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int IsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString BundleImageUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int IsLimitedEdition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int LimitedEditionIntialCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString CustomMetaData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FContainerBundleContents BundleContents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FEntitlements Entitlement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FVirtualCurrencyReward VirtualCurrency;



};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBundlesData : public UObject
{
	GENERATED_BODY()
	
};
