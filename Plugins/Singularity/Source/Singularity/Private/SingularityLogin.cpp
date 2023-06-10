// Copyright Singularity, Neobrix 2023. All rights reserved.

#include "SingularityLogin.h"
#include "WebBrowser.h"
#include "SWebBrowser.h"
#include "CoreMinimal.h"
#include "Async/Async.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/JsonSerializer.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "SingularitySaveGame.h"

#define LOCTEXT_NAMESPACE "SingularityLogin"

void USingularityLogin::startLogin()
{
    USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
    SaveGameInstance->SaveSlotName = "Singularity";
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
    if ( WebBrowserWidget.IsValid())
    {
        WebBrowserWidget->LoadURL("https://mobile-sdk.s9y.gg/?api_key="+api_key+"&env_key="+env_key);
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("https://mobile-sdk.s9y.gg/?api_key="+api_key+"&env_key="+env_key));
    }
}

void USingularityLogin::openDrawer()
{
    if (WebBrowserWidget.IsValid())
    {
        return WebBrowserWidget->ExecuteJavascript("window.SingularityEvent.open();");
    }
}

void USingularityLogin::customLogin(const FString& loginPlatform, const FString& accessToken, const FString& idToken)
{
    if (WebBrowserWidget.IsValid())
    {
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("window.SingularityEvent.customAuth(\""+loginPlatform+"\",\""+accessToken+"\",\""+idToken+"\")"));
        return WebBrowserWidget->ExecuteJavascript("window.SingularityEvent.customAuth(\""+loginPlatform+"\",\""+accessToken+"\",\""+idToken+"\")");
    }
}

FString USingularityLogin::getNtfsData()
{
    USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
    SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, 0));
    if (!SaveGameInstance)
    {
        return "";
    }
    return SaveGameInstance->NtfsData;
}

FString USingularityLogin::getUserData()
{
    USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
    SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, 0));
    if(!SaveGameInstance) {
        return "";
    }
    return SaveGameInstance->UserData;
}


TSharedRef<SWidget> USingularityLogin::RebuildWidget()
{
    if ( IsDesignTime() )
    {
        return SNew(SBox)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
        [
            SNew(STextBlock)
                .Text(LOCTEXT("Singularity Login", "Singularity Login"))
        ];
    }
    else
    {
        WebBrowserWidget = SNew(SWebBrowser)
            .InitialURL(InitialURL)
            .ShowControls(false)
            .SupportsTransparency(bSupportsTransparency)
            .OnUrlChanged(BIND_UOBJECT_DELEGATE(FOnTextChanged, HandleOnUrlChanged))
            .OnBeforePopup(BIND_UOBJECT_DELEGATE(FOnBeforePopupDelegate, HandleOnBeforePopup))
            .OnConsoleMessage(BIND_UOBJECT_DELEGATE(FOnConsoleMessageDelegate, HandleOnConsoleMessage));
        
        return WebBrowserWidget.ToSharedRef();
    }
}

void USingularityLogin::HandleOnUrlChanged(const FText& InText)
{
    OnUrlChanged.Broadcast(InText);
}

void USingularityLogin::HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity)
{
    if (Message.Contains("singularityLogoutEvent")) {
        USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
        SaveGameInstance->UserData = "";
        SaveGameInstance->NtfsData = "";
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
        OnSingularityLogout.Broadcast(Message);
    } else if (Message.Contains("singularityUserInfo")) {
        USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
        SaveGameInstance->UserData = Message;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
        OnSingularityLogin.Broadcast(Message);
    } else if (Message.Contains("singularityCloseEvent")) {
        OnSingularityClose.Broadcast(Message);
    } else if (Message.Contains("onSocialLoginButtonClicked")) {
        // Array of json objects at top level of json
        TSharedPtr<FJsonObject> JsonObject;
        
        // Create a reader pointer to read the json data
        TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Message);
        
        // Deserialize the json data given Reader and the actual object to deserialize
        if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
            // Get the value of the json object by field name
            TSharedPtr<FJsonObject> GetField = JsonObject->GetObjectField("onSocialLoginButtonClicked");
            FString name = GetField->GetStringField("socialLoginType");
            FString url = "https://auth0.s9y-sandbox.gg?platform=android&appId=unreal&loginMethod="+name;
            OnSingularitySocailLogin.Broadcast(url);
        }
    } else if (Message.Contains("ownedNfts")) {
        USingularitySaveGame* SaveGameInstance = Cast<USingularitySaveGame>(UGameplayStatics::CreateSaveGameObject(USingularitySaveGame::StaticClass()));
        SaveGameInstance->NtfsData = Message;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
        OnNftsRecieved.Broadcast(Message);
    } else  {
        OnConsoleMessage.Broadcast(Message, Source, Line);
    }
}

bool USingularityLogin::HandleOnBeforePopup(FString URL, FString Frame)
{
    if (OnBeforePopup.IsBound())
    {
        if (IsInGameThread())
        {
            OnBeforePopup.Broadcast(URL, Frame);
        }
        else
        {
            // Retry on the GameThread.
            TWeakObjectPtr<USingularityLogin> WeakThis = this;
            FFunctionGraphTask::CreateAndDispatchWhenReady([WeakThis, URL, Frame]()
                                                           {
                if (WeakThis.IsValid())
                {
                    WeakThis->HandleOnBeforePopup(URL, Frame);
                }
            }, TStatId(), nullptr, ENamedThreads::GameThread);
        }
        
        return true;
    }
    
    return false;
}

#undef LOCTEXT_NAMESPACE
