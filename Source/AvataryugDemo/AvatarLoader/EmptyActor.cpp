// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyActor.h"

// Sets default values
AEmptyActor::AEmptyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEmptyActor::BeginPlay() { Super::BeginPlay(); }
void AEmptyActor::ShowHideActor(bool show) {
  if (show) {
	SetActorHiddenInGame(false);
  } else {
    SetActorHiddenInGame(true);
  }
}


