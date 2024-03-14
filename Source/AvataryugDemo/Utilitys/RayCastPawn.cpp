// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCastPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARayCastPawn::ARayCastPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called every frame
void ARayCastPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		// {
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		// }
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

// Called to bind functionality to input
void ARayCastPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ARayCastPawn::TriggerClick);
}

void ARayCastPawn::CalcCamera(float DeltaTime, FMinimalViewInfo &OutResult)
{
		Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ARayCastPawn::TriggerClick()
{
	 UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----->>>>"));
}

void ARayCastPawn::TraceForBlock(const FVector &Start, const FVector &End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		 UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG--HITING--->>>>"));
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,HitResult.GetActor()->GetFName().ToString());
	}
}
