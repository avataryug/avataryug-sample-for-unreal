// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "AvatarGeneratedPopup.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UAvatarGeneratedPopup : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UImage *GeneratedAvatarImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock*MeshurlText;

	UPROPERTY(meta = (BindWidget))
	class UButton *CopyMeshurlButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ImageurlText;

	UPROPERTY(meta = (BindWidget))
	class UButton *CopyImageurlButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *OkButton;

	UFUNCTION()
	void CopyMeshUrl();

	UFUNCTION()
	void CopyImageUrl();

	UFUNCTION()
	void ClosePopup();

  	AAPIEvents *APIEvents;	
public:
	UFUNCTION()
	void LoadAvatarGeneratedPanelData(FString meshurl, FString imageurl);
};
