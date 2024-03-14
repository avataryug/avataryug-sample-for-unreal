// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControllerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "../Utilitys/CustomizeFacePoint.h"
#include "../AvatarLoader/AvatarHandler.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACameraControllerPawn::ACameraControllerPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}


// Called when the game starts or when spawned
void ACameraControllerPawn::BeginPlay()
{
	Super::BeginPlay();

    NextLocation = FVector(0,0, 0);
	NextRotation = FRotator(0, 0, 0);
	this->SetActorLocation(NextLocation);
    this->SetActorRotation(NextRotation, ETeleportType::None);

	if(CameraComponent == nullptr)
	{
		CameraComponent = FindComponentByClass<UCameraComponent>();
	}

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
        	APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }

  

    APIEvents->OnChangeCamera.RemoveDynamic(this, &ACameraControllerPawn::OnChangeCameraView);
    APIEvents->OnChangeCamera.AddDynamic(this, &ACameraControllerPawn::OnChangeCameraView);
}



// Called every frame
void ACameraControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		// {
			
		// }
		// else
		// {
		// 	FVector Start, Dir, End;
		// 	PC->DeprojectMousePositionToWorld(Start, Dir);
		// 	End = Start + (Dir * 8000.0f);
		// 	TraceForBlock(Start, End, false);
		// }
	}

}

// Called to bind functionality to input
void ACameraControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
//	PlayerInputComponent->BindAction("TriggerClick", IE_Pressed, this, &ACameraControllerPawn::DrawMouseRaycast);
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACameraControllerPawn::HandleTouchInput);

}

void ACameraControllerPawn::CalcCamera(float DeltaTime, FMinimalViewInfo &OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	// OutResult.Rotation = GetActorRotation();
}

void ACameraControllerPawn::HandleTouchInput(ETouchIndex::Type FingerIndex, FVector Location)
{
    // Call DrawTouchRaycast with the touch coordinates
	   if (FingerIndex == ETouchIndex::Touch1)
    {
        // Call DrawTouchRaycast with the touch coordinates
        DrawTouchRaycast(Location.X, Location.Y);
    }
    // DrawTouchRaycast(Location.X, Location.Y);
}
void ACameraControllerPawn::TriggerClick()
{
	// if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
	// {
			// FVector Start = this->GetActorLocation();
			// FVector End = Start + (this->GetActorRotation().Vector() * 1000000000.0f);

			FVector Start = CameraComponent->GetComponentLocation();
			FVector End = Start + (CameraComponent->GetComponentRotation().Vector() * 1000000000.0f);
			TraceForBlock(Start, End, true);
	// }
	// UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----->>>>"));
}
void ACameraControllerPawn::TraceForBlock(const FVector &Start, const FVector &End, bool bDrawDebugHelpers)
{
		
	FHitResult HitResult;
	// bool actorhit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility,FCollisionQueryParams());
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(10.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG--HITING--->>11111111>> %s"),*HitResult.GetActor()->GetFName().ToString());
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,HitResult.GetActor()->GetFName().ToString());
	}
	// if(actorhit && HitResult.GetActor())
	// {
		
	// 	GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,HitResult.GetActor()->GetFName().ToString());
	// }
}
void ACameraControllerPawn::Ray()
{
	 UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----RAY NEW->>>>"));
	FVector start = this->GetActorLocation();
	FVector forward = this->GetActorRotation().Vector();

	start = FVector(start.X +(forward.X * 100),start.Y + (forward.Y * 100),start.Z + (forward.Z * 100));

	FVector end = start + (forward * 100000);

	FHitResult hit;

	if(GetWorld())
	{
		
		//  UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----RAY NEW->>>>%s"),*hit.GetActor()->GetName());
		bool actorHit = GetWorld()->LineTraceSingleByChannel(hit,start,end,ECC_Visibility,FCollisionQueryParams(),FCollisionResponseParams());
		// DrawDebugLine(GetWorld(),start,end,FColor::Red, true ,2.0f,0.f,10.f);
		DrawDebugLine(GetWorld(),start,end,FColor(255,0,0),true);
		if(actorHit)
		{
		 UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----RAY NEW->22222222>>>"));
		}
		if(actorHit && hit.GetActor())
		{
			UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG--HITING--->>>> %s"),*hit.GetActor()->GetFName().ToString());
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,hit.GetActor()->GetFName().ToString());
		}
	}

}

void ACameraControllerPawn::RayCAsterOP()
{
	// UCameraComponent* OurCamera = this->FindComponentByClass<UCameraComponent>();
	FHitResult* hitrest = new FHitResult();
	FVector StartTrace = CameraComponent->GetComponentLocation();
	FVector ForwardVec = CameraComponent->GetForwardVector();
	FVector endTrace = (ForwardVec * 5000.f) + StartTrace;

	FCollisionQueryParams* CQP = new FCollisionQueryParams();


	if(GetWorld()->GetWorld()->LineTraceSingleByChannel(*hitrest,StartTrace,endTrace,ECC_Visibility,*CQP))
	{
		DrawDebugLine(GetWorld(),StartTrace,endTrace,FColor(255,0,0),true);
	}

	if(hitrest->GetActor() != NULL)
	{
		// UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG--HITING--->>>> %s"),*hitrest.GetActor()->GetFName().ToString());
		hitrest->GetActor()->Destroy();
	}


}
void ACameraControllerPawn::DrawMouseRaycast()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController)
    {
        return;
    }

    FVector MouseLocation, MouseDirection;
    if (!PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
    {
        return;
    }
	UE_LOG(LogTemp, Display, TEXT("MOUSE POINT RAYCASTINGG----->>>>"));
    FVector RayStart = MouseLocation;
    FVector RayEnd = MouseLocation + MouseDirection * 10000.f;

    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("MouseRaycastTrace")), true, this);
    GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, TraceParams);

    if (HitResult.GetActor())
    {
		ACustomizeFacePoint* point  = Cast<ACustomizeFacePoint>(HitResult.GetActor());
		FString HitActorName;
		if(point)
		{
			HitActorName = point->PointsName;

			APIEvents->OnBlendshapePoint.Broadcast(HitActorName);
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *HitActorName);
		}
    }

    DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Red, false, -1.0f, 0, 0.08f);
}

void ACameraControllerPawn::OnChangeCameraView(CameraPanels panels)
{
  	// if (Camera != nullptr)
    // {

		StartLocation = GetActorLocation();
		if (panels == CameraPanels::Lobby)
		{

			if(APIEvents->isRotated)
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::Lobby  Landscape"));
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(0, 519, 69);
				NextRotation = FRotator(0, 0, 0);
				// TimeElapsed = 0;
				LerpDuration = 0.3;
				isHeadClicked = false;
				isLerp = true;
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::Lobby  4"));
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(0, 20, 15);
				NextRotation = FRotator(0, 0, -10);
				// TimeElapsed = 0;
				LerpDuration = 0.3;
				isHeadClicked = false;
				isLerp = true;
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
				FString nerew = this->GetActorLocation().ToString();
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::Lobby  4 %s"),*nerew);
				// UE_LOG(LogTemp, Display, TEXT("currentSelectedBodyParts %d"),currentSelectedBodyParts.Num());
			}
			// Landscape 
			// transfrom(0,519,69)
			// rotation(0,0,0)
    	}
        if (panels == CameraPanels::OnBoarding)
        {
          UE_LOG(LogTemp, Display, TEXT("CameraPanels::OnBoarding"));
			// RotYaw = 0;
			// Camera->SetFieldOfView(40.0f);
			NextLocation = FVector(0, 61, 19.0f);
			NextRotation = FRotator(0, 0, -15);
			this->SetActorLocation(NextLocation);
			this->SetActorRotation(NextRotation, ETeleportType::None);
		
		}
		if (panels == CameraPanels::CustomizeAvatar_FullBody)
        {

			if(APIEvents->isRotated)
			{
				
			// Landscape 
			// transfrom(49,345,36)
			// rotation(13.021,0,7.83) x= 7.8 , y = 0 , z = 13.021
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_FullBody"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(49, 345, 36);
				NextRotation = FRotator(0.0f, 13.021f, 7.8f);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_FullBody"));
					// RotYaw = 0;
					// Camera->SetFieldOfView(40.0f);
					NextLocation = FVector(0, 185, -27);
					NextRotation = FRotator(0, 0, -10);
					this->SetActorLocation(NextLocation);
					this->SetActorRotation(NextRotation, ETeleportType::None);
			}
		}
		if (panels == CameraPanels::CustomizeAvatar_Head)
        {
			if(APIEvents->isRotated)
			{
				// Landscape 
				// transfrom(42,-69.0,91)
				// rotation(3.6,1.5,10.59) x= 3.6 , y = 1.5 , z = 12.4
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_Head"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(42, -69, 91);
				NextRotation = FRotator(1.5f, 12.4f, 3.6f);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_Head"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(0, -90, 40);
				NextRotation = FRotator(0, 0, -10);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}



		}
		if (panels == CameraPanels::CustomizeAvatar_Zoom)
        {

			if(APIEvents->isRotated)
			{
				// Landscape 
				// transfrom(0,278,67)
				// rotation(y0,z0,x1) x= 0, y = 0 , z = 0
				NextLocation = FVector(0, 278, 67);
				NextRotation = FRotator(0, 0, 0);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_Zoom"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(0, 0, 12);
				NextRotation = FRotator(0, 0, -10);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}



		
		}
		if (panels == CameraPanels::CustomizeBlendShape_Side)
        {
			if(APIEvents->isRotated)
			{
				// Landscape 
				// transfrom(-48,-65,83)
				// rotation(y0,z0,x1) x= 1, y = 0 , z = -35.0
				NextLocation = FVector(-48,-65, 83);
				NextRotation = FRotator(0, -35, 1);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeBlendShape_Side"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				NextLocation = FVector(-91,-124, 113);
				NextRotation = FRotator(0, -35, 14);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}



		
		}
		if (panels == CameraPanels::CustomizeBlendShape_Front)
        {
			if(APIEvents->isRotated)
			{
				// Landscape 
				// transfrom(0,-91,81)
				// rotation(y0,z0,x1) x= 1, y = 0 , z = 0

				NextLocation = FVector(0, -91, 81);
				NextRotation = FRotator(0, 0, 1);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);				
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeBlendShape_Front"));
				NextLocation = FVector(0, -149, 113);
				NextRotation = FRotator(0, 0, 14);
				this->SetActorLocation(NextLocation);
				this->SetActorRotation(NextRotation, ETeleportType::None);
			}

		
		}
	// 	StartLocation = GetActorLocation();
	// 	if (panels == CameraPanels::Lobby)
	// 	{
	// 	UE_LOG(LogTemp, Display, TEXT("CameraPanels::Lobby  4"));
	// 				Camera->SetFieldOfView(40.0f);
	// 				// NextLocation = FVector(33, 0, 18);
	// 				// NextRotation = FRotator(-10, 0, 0);
	// 				// NextLocation = FVector(-90, 0, 22);
	// 				// NextRotation = FRotator(-30, 0, 0);
	// 				NextLocation = FVector(31, 0, 39);
	// 				NextRotation = FRotator(-15, 0, 0);
	// 				// TimeElapsed = 0;
	// 				LerpDuration = 0.3;
	// 				isHeadClicked = false;
	// 				isLerp = true;
    // 	}
    //     if (panels == CameraPanels::OnBoarding)
    //     {
    //       UE_LOG(LogTemp, Display, TEXT("CameraPanels::OnBoarding"));
	// 		// RotYaw = 0;
	// 		Camera->SetFieldOfView(40.0f);
	// 		NextLocation = FVector(31, 0, 39);
	// 		NextRotation = FRotator(-15, 0, 0);
	// 		this->SetActorLocation(NextLocation);
	// 		this->SetActorRotation(NextRotation, ETeleportType::None);
		
	// 	}
	// }
}
void ACameraControllerPawn::OnMouseClicked()
{
    // Get the player controller
    // APlayerController* PlayerController = Cast<APlayerController>(GetController());
    // if (!PlayerController)
    // {
    //     return;
    // }

    FVector CameraLocation;
    FRotator CameraRotation;

    // Get the camera location and rotation
    if (CameraComponent)
    {
        CameraLocation = CameraComponent->GetComponentLocation();
        CameraRotation = CameraComponent->GetComponentRotation();
    }
    else
    {
        // Handle the case when the camera component is not set
		UE_LOG(LogTemp, Display, TEXT("NOW CAMERA--TO--RAY NEW->>>>"));
        return;
    }

    // Calculate the end point of the raycast
    FVector RayEnd = CameraLocation + CameraComponent->GetForwardVector() * 50000.f;

    // Perform the raycast
    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("RaycastTrace")), true, this);
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, RayEnd, ECC_Visibility, TraceParams);

    // Draw a debug line to visualize the raycast
    DrawDebugLine(GetWorld(), CameraLocation, RayEnd, FColor::Red, false, -1.0f, 0, 10.0f);
}
void ACameraControllerPawn::DrawTouchRaycast(float TouchX, float TouchY)
{
    // Ensure that you have a valid player controller
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        return;
    }

    // Convert touch coordinates to world space
    FVector WorldLocation, WorldDirection;
    PlayerController->DeprojectScreenPositionToWorld(TouchX, TouchY, WorldLocation, WorldDirection);

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