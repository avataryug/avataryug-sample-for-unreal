// Fill out your copyright notice in the Description page of Project Settings.


#include "ScenePlaner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AScenePlaner::AScenePlaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScenePlaner::BeginPlay()
{
	Super::BeginPlay();
	// if(ScenePlaneMeshComponent == nullptr)
    // {
	// 	AActor* MyActor = GetOwner();

	// 	// Find the StaticMeshComponent in the actor's components
	// 	UStaticMeshComponent* StaticMeshComponent = MyActor->FindComponentByClass<UStaticMeshComponent>();

	// 	// Check if the StaticMeshComponent is valid
	// 	if (StaticMeshComponent)
	// 	{
	// 		ScenePlaneMeshComponent = StaticMeshComponent;
	// 	}
    // }
}

// Called every frame
void AScenePlaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

