// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "CoinPanel.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "CoinHeaderPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UCoinHeaderPanel : public UUserWidget
{
  	GENERATED_BODY()
  
protected:
    void NativeConstruct() override;

    UPROPERTY()
    AAPIEvents *APIEvents;

    UPROPERTY(meta = (BindWidget))
    class UButton *CoinButton;

  public:
    UFUNCTION()
    void SetCoins();
    UFUNCTION()
    void OnClickCoinButtons();
    AUserDetailHolder *UserDetailHolder;


  UPROPERTY( meta = ( BindWidget ) )
  class UListView *CurrencyListView;
  
};
