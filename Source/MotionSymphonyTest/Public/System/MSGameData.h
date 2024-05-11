// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MSGameData.generated.h"

class UObject;
/**
 *
 */
UCLASS( Blueprintable, Const,
        meta = ( DisplayName  = "MS Game Data",
                 ShortToolTip = "Data Asset containing global game data." ) )
class MOTIONSYMPHONYTEST_API UMSGameData : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UMSGameData();

    static const UMSGameData& Get();
};
