// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GltfStaticActorPoint.generated.h"

UCLASS()
class AVATARYUGDEMO_API AGltfStaticActorPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGltfStaticActorPoint();


public:	

   UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Point")
    FString BucketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Point")
	int VertexIndex;
};
