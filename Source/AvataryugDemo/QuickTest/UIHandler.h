// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AvatarLoaderUI.h"
#include "UIHandler.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API AUIHandler : public AHUD
{
	GENERATED_BODY()
public:
	AUIHandler();

	void DrawHUD() override;

	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TSubclassOf<UAvatarLoaderUI> WBP_AvatarLoaderUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	UAvatarLoaderUI* AvatarLoaderUI;
	
};
