// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DefaultAPI/DefaultModels.h"
#include "CommonFunction.h"
#include "LocalDataFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FBodywearPointDetail
{
  GENERATED_USTRUCT_BODY()
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FString PointName;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FString BoneName;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FVector Position;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FRotator Rotation;
};

USTRUCT(BlueprintType)
struct FFacePoint
{
  GENERATED_USTRUCT_BODY()

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
};

USTRUCT(BlueprintType)
struct FVertexBucketPoint
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FString BucketName;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  FString MainCatID;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
  TArray<int32> VertexArray;
};

// USTRUCT(BlueprintType)
// struct FVertexBucketPoint
// {
//   GENERATED_BODY()
//   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
//   TArray<FVertexBucketPoint> data ;
// };

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API ULocalDataFunctionLibrary : public UBlueprintFunctionLibrary
{
public:
  GENERATED_BODY()
  static TArray<FBodywearPointDetail> GetBodyLocalPointList();

  static TArray<FModelDataResponce> GetDefaultModelList(FString gender);

  static FModelDataResponce GetEmptyModelDataClass();

  static TArray<FFacePoint> GetEarshape();
  static TArray<FFacePoint> GetNoseShape();
  static TArray<FFacePoint> GetEyebrowShape();
  static TArray<FFacePoint> GetEyeShape();
  static TArray<FFacePoint> GetLipShape();
  static TArray<FFacePoint> GetFaceShape();

  static TArray<FGetAllBucketVerticesResultDataInner> GetVertices();

  static TArray<FVertexBucketPoint> GetBucketVertices();

  // static TArray<FVertexBucketPoint> ParseJsonDataAndPopulateTArray();

  // TArray<FVertexData> ParsedVertexData;
};
