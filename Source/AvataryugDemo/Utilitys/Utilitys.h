// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameEnums.h"
#include "Utilitys.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UUtilitys : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  static FString GetPlatform();
	
  
};
