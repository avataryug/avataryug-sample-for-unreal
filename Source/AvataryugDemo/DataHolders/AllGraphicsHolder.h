// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AllGraphicsHolder.generated.h"

USTRUCT(BlueprintType)
struct FGraphicsWithID
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	UTexture2D *Texture;
};


UCLASS()
class AVATARYUGDEMO_API AAllGraphicsHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAllGraphicsHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FGraphicsWithID> GraphicsWithIDList;
	UFUNCTION()
    void AddGraphics(UTexture2D *texture, FString id);
    UFUNCTION()
    bool IsGraphicsPresent(FString id);
	UFUNCTION()
    FGraphicsWithID GetGraphics(FString id);
};
