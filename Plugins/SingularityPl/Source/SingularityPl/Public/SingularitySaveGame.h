// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SingularitySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SINGULARITYPL_API USingularitySaveGame : public USaveGame
{
	GENERATED_BODY()
    
public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString UserData;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString NtfsData;
    
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

};
