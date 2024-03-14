// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptyActor.generated.h"

UCLASS()
class AVATARYUGDEMO_API AEmptyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

      public:
        void ShowHideActor(bool show);
};
