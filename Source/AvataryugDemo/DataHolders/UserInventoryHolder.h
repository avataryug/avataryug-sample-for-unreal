// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "UserInventoryHolder.generated.h"

UCLASS()
class AVATARYUGDEMO_API AUserInventoryHolder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUserInventoryHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<FGetUserInventoryResultDataInner> Inventory;
	UFUNCTION()
	void LogOut();
	UFUNCTION()
	void AddUserInventory(TArray<FGetUserInventoryResultDataInner> inventoryList);
	UFUNCTION()
	bool IsPresentInventory(FString id);
	UFUNCTION()
	TArray<FGetUserInventoryResultDataInner> GetInventoryList();
};
