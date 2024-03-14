// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInventoryHolder.h"


// Sets default values
AUserInventoryHolder::AUserInventoryHolder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUserInventoryHolder::BeginPlay()
{
	Super::BeginPlay();
}
void AUserInventoryHolder::LogOut()
{
}

void AUserInventoryHolder::AddUserInventory(TArray<FGetUserInventoryResultDataInner> inventoryList)
{
	Inventory = inventoryList;
}

bool AUserInventoryHolder::IsPresentInventory(FString id)
{
	bool isPresent = false;
	if (Inventory.Num() > 0)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i].InstanceID == id)
			{
				isPresent = true;
				break;
			}
		}
	}
	return isPresent;
}

TArray<FGetUserInventoryResultDataInner> AUserInventoryHolder::GetInventoryList()
{
	TArray<FGetUserInventoryResultDataInner> FoundStructs;
	for (const auto &item : Inventory)
	{
		// if (item.InstanceType != "ITEM" && item.Count > 0)
		//{
		FoundStructs.Add(item);
		//}
	}
	return FoundStructs;
}
