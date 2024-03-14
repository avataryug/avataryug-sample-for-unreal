// Fill out your copyright notice in the Description page of Project Settings.


#include "AllGraphicsHolder.h"

// Sets default values
AAllGraphicsHolder::AAllGraphicsHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAllGraphicsHolder::BeginPlay()
{
	Super::BeginPlay();
	
}



void AAllGraphicsHolder::AddGraphics(UTexture2D *texture, FString id)
{
  	bool isPresent = false;
    for (int i = 0; i < GraphicsWithIDList.Num(); i++)
	{
        if (GraphicsWithIDList[i].ID == id)
        {
          	isPresent = true;
          	break;
		}
	}
    if (!isPresent)
    {
      	FGraphicsWithID twithid;
      	twithid.ID = id;
      	twithid.Texture = texture;
      	GraphicsWithIDList.Add(twithid);
	}
}
bool AAllGraphicsHolder::IsGraphicsPresent(FString id)
{
	bool isPresent = false;
    for (int i = 0; i < GraphicsWithIDList.Num(); i++)
	{
        if (GraphicsWithIDList[i].ID == id)
        {
          	isPresent = true;
          	break;
		}
    }
    return isPresent;
}
FGraphicsWithID AAllGraphicsHolder::GetGraphics(FString id)
{
	FGraphicsWithID twithid;
    for (int i = 0; i < GraphicsWithIDList.Num(); i++)
	{
        if (GraphicsWithIDList[i].ID == id)
        {
          	twithid = GraphicsWithIDList[i];
          	break;
		}
    }
    return twithid;
}