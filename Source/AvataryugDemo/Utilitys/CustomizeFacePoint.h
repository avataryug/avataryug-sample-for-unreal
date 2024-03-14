// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomizeFacePoint.generated.h"

UCLASS()
class AVATARYUGDEMO_API ACustomizeFacePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomizeFacePoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(VisibleAnywhere)
  UStaticMeshComponent *SuperMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    int VertexNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    FString partType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    FString HorizontalShape;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    FString VerticalShape;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    FString ViewDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    UStaticMeshComponent *PlaneMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    FString PointsName;

  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  	class UMaterial *pointMaterial;
    
  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  	UMaterialInstanceDynamic *pointDynamicMaterial;
};
