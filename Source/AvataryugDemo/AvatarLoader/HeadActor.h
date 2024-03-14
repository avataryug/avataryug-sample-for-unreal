// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultAPI/DefaultModels.h"
#include "DefaultAPI/DefaultRequest.h"
#include "GltfStaticActorPoint.h"
#include "DefaultAPI/DefaultHandler.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Kismet/KismetStringLibrary.h"
#include "../DataHolders/LocalDataFunctionLibrary.h"
#include "Engine/SkeletalMeshSocket.h"
#include "SkeletalRenderPublic.h"
#include "HeadActor.generated.h"

UCLASS()
class AVATARYUGDEMO_API AHeadActor : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AHeadActor();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
  USkeletalMeshComponent *SkeletalHeadComponent;
  void SetBodyMaterial(UMaterialInstanceDynamic *material);
  void SetEyeMaterial(UMaterialInstanceDynamic *material);
  void SetMouthMaterial(UMaterialInstanceDynamic *material);
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 vertexPointValue = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|Material")
  UMaterialInstanceDynamic *DynamicFaceMaterial;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Eyeball")
  UMaterialInstanceDynamic *DynamicEyeMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Eyeball")
  UMaterialInstanceDynamic *DynamicMouthMaterial;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|BodyWearSocket")
  USkeleton *mySkeleton;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|BodyWearSocket")
  USkeletalMeshSocket *mySocket;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|BodyWearSocket")
  TArray<USkeletalMeshSocket *> bodyPointSocket;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
  TArray<FVertexBucketPoint> VertexPoints;

  void ChangeBlendshapeValue(FString blendshapename, float value);
  void ClearBlendShapeWithname(FString blendshapename);
  void ClearAllBlendShape();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|Vertex")
  TArray<FVector> Locations;

  UPROPERTY()
  FOnGetAllBucketVerticesResult GetAllBucketVerticesResult;
  UFUNCTION()
  void OnGetAllBucketVerticesResult(FGetAllBucketVerticesResult result);
  UPROPERTY()
  FOnApiException GetAllBucketVerticesError;
  UFUNCTION()
  void OnGetAllBucketVerticesError(FApiException result);

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|Vertex")
  TArray<AGltfStaticActorPoint *> vertexPointsAdded;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug|Face|Vertex")
  TSubclassOf<class AGltfStaticActorPoint> vertexPointActor_BP;
  UFUNCTION()
  void SetBodyPartColor(FLinearColor OutColor, FString category);

  UFUNCTION()
  void LoadVertexPoints();

  UFUNCTION(BlueprintCallable)
  void IncrementValue();
  UFUNCTION(BlueprintCallable)
  void DecrementValue();
};
