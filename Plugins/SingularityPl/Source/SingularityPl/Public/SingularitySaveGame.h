// Copyright Singularity, Neobrix 2023. All rights reserved.

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
