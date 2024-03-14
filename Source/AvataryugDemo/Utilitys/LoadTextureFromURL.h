// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadTextureFromURL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnReceiveTexture, UTexture2D *, texture);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnReceiveData, TArray<uint8>, byteData);
/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API ULoadTextureFromURL : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    static void LoadTexture(FString url, FOnReceiveTexture result);
    UFUNCTION(BlueprintCallable)
    static void LoadByte(FString url, FOnReceiveData result);
    static void LoadByte(FString url, TFunction<void(UTexture2D *)> result);
    static void LoadByte(FString url, TFunction<void(TArray<uint8>)> result);
    UFUNCTION(BlueprintCallable)
    static TArray<uint8> GetModelByte(TArray<uint8> inputdata);

private:
    static TArray<uint8> decryptAES(const TArray<uint8> &CipherText, const TArray<uint8> &Key, const TArray<uint8> &IV);
    static TArray<uint8> unpad(const TArray<uint8> &Data, int BlockSize);
    static TArray<uint8> StringToByteArray(const FString &String);
};
