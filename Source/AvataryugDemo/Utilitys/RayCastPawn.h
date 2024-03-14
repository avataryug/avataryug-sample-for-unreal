// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RayCastPawn.generated.h"

UCLASS()
class AVATARYUGDEMO_API ARayCastPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	// UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	// class APuzzleTestBlock* CurrentBlockFocus;

};
