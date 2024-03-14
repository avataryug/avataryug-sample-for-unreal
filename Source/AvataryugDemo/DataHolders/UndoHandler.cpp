// Fill out your copyright notice in the Description page of Project Settings.


#include "UndoHandler.h"

// Sets default values
AUndoHandler::AUndoHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUndoHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndoHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndoHandler:: OnClickUndo(){}