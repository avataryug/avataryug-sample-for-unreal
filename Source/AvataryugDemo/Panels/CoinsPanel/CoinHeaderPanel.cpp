// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinHeaderPanel.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
void UCoinHeaderPanel::NativeConstruct()
{
    Super::NativeConstruct();

    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        if(UserDetailHolder == nullptr)
        {
            UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
        }
    }

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }

    CoinButton->OnClicked.RemoveDynamic(this, &UCoinHeaderPanel::OnClickCoinButtons);
    CoinButton->OnClicked.AddDynamic(this, &UCoinHeaderPanel::OnClickCoinButtons);

}

void UCoinHeaderPanel::SetCoins()
{
  	TArray<FWallet> wallets = UserDetailHolder->UserDetails.wallets.wallets;
   
    if(CurrencyListView)
    {
        CurrencyListView->ClearListItems();
    }
    for(int i = 0 ; i < wallets.Num();i++ )
    {
        UCurrencyItemData *item = NewObject<UCurrencyItemData>();
        item->Index = i;
        item->CurrencyAmount = FString::FromInt(wallets[i].Amount);
        item->CurrencyCode = wallets[i].VirtualCurrency;
        CurrencyListView->AddItem(item);
    }
}

void UCoinHeaderPanel::OnClickCoinButtons()
{
   APIEvents->ShowPanel(EUIPanels::CURRENCYSTORE, true);
   UE_LOG(LogTemp, Display, TEXT("OPEN COIN STORE--->>"));
}