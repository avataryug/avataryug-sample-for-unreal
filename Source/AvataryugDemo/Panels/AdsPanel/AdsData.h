// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdsData.generated.h"

USTRUCT(BlueprintType)
struct FAdsMetaData
{
  	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString InstanceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString InstanceType;
};


USTRUCT(BlueprintType)
struct FActionArrays
{
   	GENERATED_USTRUCT_BODY()

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FAdsMetaData MetaData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Quantity;
};


USTRUCT(BlueprintType)
struct FAdsReward
{
    GENERATED_USTRUCT_BODY()

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString RewardURL;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FActionArrays> ActionArray;

 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    bool Selected;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    bool Checked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Odds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int32 ID;
};

USTRUCT(BlueprintType)
struct FAdsRewards
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FAdsReward> adsRewards;
};
USTRUCT(BlueprintType)
struct FAdsLimit
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString LimitCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString LimitHours;
};
USTRUCT(BlueprintType)
struct FAdsPlacementClass
{
   	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString PlacementName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Platform;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString AdFormat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString AdUnit;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FAdsRewards Rewards;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Segments;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FAdsLimit AdLimits;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    int32 Status;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ID;
};




/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UAdsData : public UObject
{
	GENERATED_BODY()
	
};
