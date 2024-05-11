// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MSPawnData.generated.h"

class APawn;
class UMSCameraMode;
class UMSInputConfig;
class UObject;
/**
 *
 */
UCLASS( BlueprintType, Const,
        meta = ( DisplayName  = "MS Pawn Data",
                 ShortToolTip = "Data Asset used to define a Pawn." ) )
class MOTIONSYMPHONYTEST_API UMSPawnData : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UMSPawnData( const FObjectInitializer& object );

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "MS|Pawn" )
    TSubclassOf< APawn > _pawnClass;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "MS|Input" )
    TObjectPtr< UMSInputConfig > _inputConfig;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "MS|Camera" )
    TSubclassOf< UMSCameraMode > _cameraMode;
};
