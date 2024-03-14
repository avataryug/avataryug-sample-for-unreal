// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Utilitys/APIEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "../Utilitys/CustomizeFacePoint.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraControllerPawn.generated.h"

UCLASS()
class AVATARYUGDEMO_API ACameraControllerPawn : public APawn
{
		GENERATED_UCLASS_BODY()

public:
	// Sets default values for this pawn's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    UCameraComponent* CameraComponent;
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	// USpringArmComponent *SpringArm;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float LerpDuration = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float WaitTime = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool isLerp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FRotator TargetRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FRotator StartRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool isHeadClicked = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool isCustomizeAvtarClicked = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool isBGChangeClicked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool isLandscapeOrientation = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

    void Ray();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	void HandleTouchInput(ETouchIndex::Type FingerIndex, FVector Location);
	void DrawTouchRaycast(float TouchX, float TouchY);
    void RayCAsterOP();
    void DrawMouseRaycast();
    UFUNCTION()
    void OnChangeCameraView(CameraPanels panels);
    void OnMouseClicked();
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MyCategory)
    FVector NextLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MyCategory)
    FRotator NextRotation;



    AAPIEvents *APIEvents;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ACustomizeFacePoint* CurrentBlockFocus;

};
