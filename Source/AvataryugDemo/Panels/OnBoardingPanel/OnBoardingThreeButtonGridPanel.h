// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnBoardingThreeAvatarButton.h"
#include "OnBoardingThree.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "OnBoardingThreeButtonGridPanel.generated.h"

/**
 *
 */
UCLASS()
class UListNewItemData : public UObject
{
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	TArray<FGetAvatarPresetsResultDataInner> presetLists;
        TFunction<void(FGetAvatarPresetsResultDataInner)> OnClickButton;
        UOnBoardingThree * OnBoardingThree;
};

UCLASS()
class AVATARYUGDEMO_API UOnBoardingThreeButtonGridPanel : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOnBoardingThreeAvatarButton *OnBoradingThreeButton_1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOnBoardingThreeAvatarButton *OnBoradingThreeButton_2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOnBoardingThreeAvatarButton *OnBoradingThreeButton_3;

	TArray<UOnBoardingThreeAvatarButton *> OnBoradingThreeButtons;
};
