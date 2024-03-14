// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "CurrentAvatarChanges.generated.h"

UCLASS()
class AVATARYUGDEMO_API ACurrentAvatarChanges : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACurrentAvatarChanges();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Avatar")
	FProps currentProps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FBlendShapeValue> currentBlendShapes;

	FPropColors currentpropColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Changes")
	FProps changedProps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FBlendShapeValue> changeBlendShapes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Changes")
	FPropColors changePropColors;

	UFUNCTION(BlueprintCallable, Category = "User Items")
	bool IsItemPresent(FString Id);

	UFUNCTION(BlueprintCallable, Category = "User Items")
	bool IsPresent(FString id);

	UFUNCTION()
	bool isPresentInCurrent(FString id);

	UFUNCTION()
	bool isPresentInCurrentShape(FBlendShapeValue blendShape);

	UFUNCTION()
	void OnChangeSkinColor(FString category, FLinearColor OutColor);

	UFUNCTION()
	void ChangeBlendshapeValue(FBlendShapeValue blendShape);

	UFUNCTION()
	void AddChangeProps(TArray<FEconomyItems> Items);

	UFUNCTION()
	void Logout();

	UFUNCTION()
	void ResetChanges();

	UFUNCTION(BlueprintCallable, Category = "BlendShapes")
	float IsPresentInChangedShape(FString ShapeKey);
};
