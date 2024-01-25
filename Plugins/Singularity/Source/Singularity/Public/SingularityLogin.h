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
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularityRequestPersonalSignature, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularitySignTransaction, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularitySignAndSendTransaction, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularitySendNonNativeToken, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularitySendNft, const FString&, Text);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSingularityRequestTypedSignature, const FString&, Text);

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
    void requestPersonalSignature(const FString& message);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void requestTypedSignature(const FString& domainJson, const FString& typeJson, const FString& messageJson, const FString& primaryType);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void sendNft(const FString& transactionJson);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void sendNonNativeToken(const FString& transactionJson);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void signAndSendTransaction(const FString& transactionJson);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void signTransaction(const FString& transactionJson);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void close();
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void logOut();
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Singularity Login"), Category = "Singularity")
    void getConnectUserInfo();
    
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
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularityRequestPersonalSignature OnSingularityRequestPersonalSignatureCallback;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularitySignTransaction OnSingularitySignTransactionCallback;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularitySignAndSendTransaction OnSingularitySignAndSendTransactionCallback;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularitySendNonNativeToken OnSingularitySendNonNativeTokenCallback;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularitySendNft OnSingularitySendNftCallback;
    
    UPROPERTY(BlueprintAssignable, Category = "Singularity Login|Event")
    FOnSingularityRequestTypedSignature OnSingularityRequestTypedSignatureCallback;
        
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);
    void HandleOnUrlChanged(const FText& Text);
    bool HandleOnBeforePopup(FString URL, FString Frame);
    
};
