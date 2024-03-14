// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContainerButton.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ContainerButtonGrid.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UContainerButtonGrid : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()


	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

protected:
	void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UContainerButton *ContainersButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UContainerButton *ContainersButton1;

	TArray<UContainerButton *> ContainersButtonList;

};
