// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

    EnableInput(this);
 	if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
	if (handler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        handler = Cast<AAvatarHandler>(FoundActor);
        if (handler == nullptr)
        {
            handler = GetWorld()->SpawnActor<AAvatarHandler>();
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
	InputComponent->BindTouch(IE_Pressed, this, &AMyPlayerController::SwipeStart);
	InputComponent->BindTouch(IE_Released, this, &AMyPlayerController::SwipeEnd);
	InputComponent->BindTouch(IE_Repeat, this, &AMyPlayerController::SwipeInput);
}
void AMyPlayerController::SwipeStart(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (FingerIndex == ETouchIndex::Touch1) {
           canRotate =true;
        // Call DrawTouchRaycast with the touch coordinates
        DrawTouchRaycast(Location.X, Location.Y);
    }
    // Store the initial touch location
    InitialSwipeLocation = Location;
}
void AMyPlayerController::SwipeEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
    // Calculate the swipe direction and perform actions
    FVector SwipeDirection = Location - InitialSwipeLocation;
    canRotate =false;
    // Continue tracking the swipe even after the initial swipe
    InitialSwipeLocation = Location;
}
void AMyPlayerController::SwipeInput(ETouchIndex::Type FingerIndex, FVector Location)
{
    FVector SwipeDirection = Location - InitialSwipeLocation;
    if (handler && canRotate)
    {
        if (!handler->stopRotate)
        {
            float RotationSpeed = 1.0f; // Adjust the rotation speed
            FRotator NewRotation = handler->GetActorRotation();
            NewRotation.Yaw -= SwipeDirection.X * RotationSpeed;
            handler->SetActorRotation(NewRotation);
        }
    }

    InitialSwipeLocation = Location;
}

void AMyPlayerController::DrawTouchRaycast(float TouchX, float TouchY)
{
    // Convert touch coordinates to world space
    FVector WorldLocation, WorldDirection;
    DeprojectScreenPositionToWorld(TouchX, TouchY, WorldLocation, WorldDirection);
    FVector RayStart = WorldLocation;
    FVector RayEnd = WorldLocation + WorldDirection * 10000.0f;
    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("TouchRaycastTrace")), true, this);
    GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, TraceParams);
    if (HitResult.GetActor())
    {
        // Assuming you have a class named ACustomizeFacePoint or similar
        ACustomizeFacePoint* Point = Cast<ACustomizeFacePoint>(HitResult.GetActor());
        FString HitActorName;
        if (Point)
        {
            HitActorName = Point->PointsName;
            // Assuming you have an event dispatcher called OnBlendshapePoint
            APIEvents->OnBlendshapePoint.Broadcast(HitActorName);
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *HitActorName);
        }
    }
    // Draw a debug line to visualize the raycast
    DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Red, false, -1.0f, 0, 0.08f);
}