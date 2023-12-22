// Copyright Singularity, Neobrix 2023. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebBrowser.h"
#include "SingularityLogin.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SINGULARITY_API USingularityLogin : public UWebBrowser
{
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUSingularityClose, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularityLogin, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularitySocialLogin, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularityLogout, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNftsRecieved, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularityInit, const FString&, Text);
    
    UPROPERTY(BlueprintReadWrite, Category = "Singularity Login|Key")
    FString api_key;
    UPROPERTY(BlueprintReadWrite, Category = "Singularity Login|Key")
    FString env_key;
    
    // Start Login Flow.
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void startLogin();
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void customLogin(const FString& loginPlatform, const FString& accessToken, const FString& idToken);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void initiateTransaction(const FString& transactionJson);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void openDrawer();
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    FString getNtfsData();
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    FString getUserData();
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnUSingularityClose OnSingularityClose;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularityLogin OnSingularityLogin;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularitySocialLogin OnSingularitySocailLogin;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularityLogout OnSingularityLogout;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnNftsRecieved OnNftsRecieved ;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularityInit OnSingularityInitCallback ;
    
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);
    void HandleOnUrlChanged(const FText& Text);
    bool HandleOnBeforePopup(FString URL, FString Frame);
    
};
