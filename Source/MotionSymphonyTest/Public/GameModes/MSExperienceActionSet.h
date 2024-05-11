// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MSExperienceActionSet.generated.h"

class UGameFeatureAction;
/**
 *
 */
UCLASS( BlueprintType, NotBlueprintable )
class MOTIONSYMPHONYTEST_API UMSExperienceActionSet : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UMSExperienceActionSet();

#if WITH_EDITOR
    virtual EDataValidationResult
    IsDataValid( class FDataValidationContext& context ) const override;
#endif

#if WITH_EDITORONLY_DATA
    virtual void UpdateAssetBundleData() override;
#endif

public:
    UPROPERTY( EditAnywhere, Instanced, Category = "Actions to Perform" )
    TArray< TObjectPtr< UGameFeatureAction > > _actions;

    UPROPERTY( EditAnywhere, Category = "Feature Dependencies" )
    TArray< FString > _gameFeaturesToEnable;
};
