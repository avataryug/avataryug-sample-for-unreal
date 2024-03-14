// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultAPI/DefaultRequest.h"
#include "DefaultAPI/DefaultHandler.h"
#include "GameFramework/Actor.h"
#include "GameEnums.h"
#include "../Utilitys/APIEvents.h"
#include "CommonModels.h"
#include "EconomyItemHolder.h"
#include "CurrentAvatarChanges.h"
#include "DataHolder.generated.h"

UCLASS()
class AVATARYUGDEMO_API ADataHolder : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ADataHolder();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  TArray<FEconomyItems> currentSelectedBodyParts;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  bool isCustomizeAvatar;
  UFUNCTION()
  void AddCurrenBodyPart(FEconomyItems item);
  UFUNCTION()
  void RemovepropItem(FEconomyItems item);
  UFUNCTION()
  void RemovepropItemWithCat(FString category);
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  FEconomyItems currentSelectedBodyPart;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  FExpression currentExpDataHolder;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  AAPIEvents *APIEvents;
  UFUNCTION()
  void SynAvatars();

  FOnSyncAvatarsResponse OnSyncAvatarsResponse;
  UFUNCTION()
  void OnSyncAvatarResponseReceive(FString resp);
  FOnApiException OnApiExceptionSync;
  
  UFUNCTION()
  void OnSyncAvatarError(FApiException result);

  UFUNCTION()
  void OnItemAddedRemoved();

  UPROPERTY()
  ACurrentAvatarChanges *CurrentAvatarChanges;

  UPROPERTY()
  bool resetToCurrentModel;

  UPROPERTY()
  bool cameFromFirstAvatar;
};
