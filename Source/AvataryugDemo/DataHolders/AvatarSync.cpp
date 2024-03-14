// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarSync.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAvatarSync::AAvatarSync()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatarSync::BeginPlay()
{
	Super::BeginPlay();

	if(CommonFunctionHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
        CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
        if (CommonFunctionHolder == nullptr)
        {
            CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
        }
    }
	
}

// Called every frame
void AAvatarSync::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	  time += DeltaTime;

	if ((UGameplayStatics::GetTimeSeconds(GetWorld()) - lastTime) > 0.1f)
    {
        if (process == "...")
        {
            process = "";
        }
        else
        {
            process += ".";
        }
        lastTime = UGameplayStatics::GetTimeSeconds(GetWorld());
    }

}

void AAvatarSync::SyncAvatars()
{
    // Set the actor's name (assuming it's attached to an actor)
    // SetActorLabel(GetClass()->GetName());

    // Convert the platform enum to string using your function GetPlatformAsString
    FString PlatformName = CommonFunctionHolder->GetPlatformAsString();

    // Perform the avatar synchronization logic
    CommonFunctionHolder->SyncAvatar(PlatformName, [this]()
    {
        CommonFunctionHolder->GetUserAllAvatars([this]()
        {
            // Log a message (equivalent to Debug.Log in Unity)
            UE_LOG(LogTemp, Warning, TEXT("SyncAvatar %f"), time);

            // Destroy the actor (equivalent to Destroy(gameObject) in Unity)
            Destroy();
        });
    });
}