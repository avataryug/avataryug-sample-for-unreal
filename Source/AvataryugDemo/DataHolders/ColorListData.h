// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ColorListData.generated.h"

/**
 *
 */
UCLASS()
class UColorListData : public UObject
{
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	FString category;
	TArray<FString> m_Colors;
};
