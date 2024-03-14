// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationYaw = false;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	cam->AttachToComponent(RootComponent, AttachmentTransformRules);
	cam->SetRelativeLocation(FVector(0, 0, 40));
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// InputComponent->BindAction("Cast",IE_Pressed,this,&AMyCharacter::Ray);
	PlayerInputComponent->BindAction("Cast", IE_Pressed, this, &AMyCharacter::Ray);


}
void AMyCharacter::Ray()
{
	UE_LOG(LogTemp, Display, TEXT("RAYCASTINGG----->>>>"));
	FVector start = GetActorLocation();
	FVector forward = cam->GetForwardVector();

	start = FVector(start.X + (forward.X * 100), start.Y + (forward.Y * 100), start.X + (forward.X * 100));

	FVector end = start + (forward * 1000);

	FHitResult hit;

	if (GetWorld())
	{
		bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Pawn, FCollisionQueryParams());
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, 0.f, 10.f);
		if (actorHit && hit.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, hit.GetActor()->GetFName().ToString());
		}
	}
}
