// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AvatarLoader/AvatarLoaderBase.h"
#include "../Utilitys/APIEvents.h"
#include "CustomizeAvatarLoader.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API ACustomizeAvatarLoader : public AAvatarLoaderBase
{
	GENERATED_BODY()

	public:

	ACustomizeAvatarLoader();

    UFUNCTION()
    void LoadDefaultModel();

    UFUNCTION()
    void EventLoadNetworkModel(bool sender, FEconomyItems e);

    UFUNCTION()
    void DownloadModelfromData(FEconomyItems itemdata); 

    // Singleton pattern to get the instance
    UFUNCTION(BlueprintCallable, Category = "CustomizeAvatarLoader")
    static ACustomizeAvatarLoader* GetInstance();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
    // Private static instance variable
    static ACustomizeAvatarLoader* Instance;
};

