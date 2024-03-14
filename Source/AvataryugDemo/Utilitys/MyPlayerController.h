// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Utilitys/APIEvents.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../Utilitys/CustomizeFacePoint.h"
#include "../AvatarLoader/AvatarHandler.h"
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void SetupInputComponent();

    UPROPERTY()
    AAPIEvents *APIEvents;

    UPROPERTY()
    AAvatarHandler *handler;
        
	UFUNCTION()
    void SwipeStart(ETouchIndex::Type FingerIndex, FVector Location);
    UFUNCTION()
    void SwipeInput(ETouchIndex::Type FingerIndex, FVector Location);
	

    bool isSwipe = false;

	UPROPERTY(EditAnywhere, Category = EndlessRunCoreSettings, meta = (DisplayName = "Minimum Swipe Distance"))
	float MinSwipeDistance = 15;

	void TouchPressed(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchMoved(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchReleased(ETouchIndex::Type FingerIndex, FVector Location);


	void SwipeEnd(ETouchIndex::Type FingerIndex, FVector Location);
	FVector2D TouchPressedLocation;

	FVector InitialSwipeLocation;
	void DrawTouchRaycast(float TouchX, float TouchY);
        // AMyPlayerController();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    bool canRotate;
};
