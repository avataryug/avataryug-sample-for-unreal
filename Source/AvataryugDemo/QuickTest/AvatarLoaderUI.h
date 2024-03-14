// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include <EconomyAPI/EconomyModel.h>
#include "../AvatarLoader/CustomizeAvatarLoader.h"
#include "AvatarLoaderUI.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UAvatarLoaderUI : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* LoginPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* AvatarLoaderPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* LoadingPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* LoginButton;

	ACustomizeAvatarLoader *CustomizeAvatarLoader;

	void NativeConstruct() override;

	UFUNCTION()
	void OnClickLoginButton();


	//Avatar Loader Panel



	UPROPERTY(meta = (BindWidget))
	class UButton* TopButton;

	UFUNCTION()
	void OnClickTopButton();

	UPROPERTY(meta = (BindWidget))
	class UButton* BottomButton;

	UFUNCTION()
	void OnClickBottomButton();

	UPROPERTY(meta = (BindWidget))
	class UButton* MoreButton;

	UFUNCTION()
	void OnClickMoreButton();

	UFUNCTION()
	FEconomyItems GetEconomyItem(FGetEconomyItemsResultDataInner data);


	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MoreDetailsPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* OkButton;

	UFUNCTION()
	void OnClickOkButton();

};
