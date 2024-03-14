// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizeFacePoint.h"

// Sets default values
ACustomizeFacePoint::ACustomizeFacePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
        
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point"));
}

// Called when the game starts or when spawned
void ACustomizeFacePoint::BeginPlay()
{
	Super::BeginPlay();
	
	//PlaneMesh = SuperMesh->GetStaticMesh();

	for (UActorComponent* ChildComponent : SuperMesh->GetAttachChildren())
	{
		// Check if the child component is a UStaticMeshComponent
		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ChildComponent);
		
		if (StaticMeshComponent)
		{
			// Assuming the static mesh component represents the plane
			PlaneMesh = StaticMeshComponent;

			// pointMaterial = PlaneMesh->GetMaterial(0);

			if(pointDynamicMaterial == nullptr)
			{
				 pointDynamicMaterial = UMaterialInstanceDynamic::Create(pointMaterial,  this);
			}

			break;
		}
	}
}

// Called every frame
void ACustomizeFacePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
