// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoreData.generated.h"


/**
 * 
 */


USTRUCT(BlueprintType)
struct FStoreVirtualCurrency
{
	GENERATED_USTRUCT_BODY()
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Amount;
	
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString UserID;
};

USTRUCT(BlueprintType)
struct FStoreContent
{
  GENERATED_USTRUCT_BODY()
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString CustomData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString UserID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FStoreVirtualCurrency> VirtualCurrency;

};

USTRUCT(BlueprintType)
struct FTestStoreVirtualCurrency
{
	GENERATED_USTRUCT_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FStoreVirtualCurrency> VirtualCurrency;
};

USTRUCT(BlueprintType)
struct FStoreContents
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FStoreContent> storecontent;
};
USTRUCT(BlueprintType)
struct FContainersBase
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
struct FContainersBundleContents
{
	GENERATED_USTRUCT_BODY()
	TArray<FContainersBase> Bundles;
	TArray<FContainersBase> Container;
	TArray<FContainersBase> Currencies;
	TArray<FContainersBase> Droptable;
	TArray<FContainersBase> Items;

};
USTRUCT(BlueprintType)
struct FMyContainerBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    FString Code;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    FString Quantity;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    FString UserID;
};
USTRUCT(BlueprintType)
struct FMyBundleContents
{
	GENERATED_BODY()
	 UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    TArray<FMyContainerBase> Bundles;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    TArray<FMyContainerBase> Container;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    TArray<FMyContainerBase> Currencies;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    TArray<FMyContainerBase> Droptable;

    UPROPERTY(BlueprintReadWrite, Category = "MyCategory")
    TArray<FMyContainerBase> Items;
};



UCLASS()
class AVATARYUGDEMO_API UStoreData : public UObject
{
	GENERATED_BODY()
};
