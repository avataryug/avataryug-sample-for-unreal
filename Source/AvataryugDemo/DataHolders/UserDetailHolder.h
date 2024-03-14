// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "UserDetailHolder.generated.h"




UCLASS()
class AVATARYUGDEMO_API AUserDetailHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserDetailHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FUserDetails UserDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FString	 tempmeshurl;
    UFUNCTION()
	void LogOut();
};
