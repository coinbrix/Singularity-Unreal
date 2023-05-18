// Copyright Singularity, Neobrix 2023. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

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
