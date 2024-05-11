// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MSExperienceDefinition.generated.h"


class UMSPawnData;
class UGameFeatureAction;
class UMSExperienceActionSet;
    /**
 *
 */
UCLASS( BlueprintType, Const )
class MOTIONSYMPHONYTEST_API UMSExperienceDefinition : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UMSExperienceDefinition();

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid( class FDataValidationContext& context ) const override;
#endif

#if WITH_EDITORONLY_DATA
    virtual void UpdateAssetBundleData() override;
#endif

public:
    UPROPERTY( EditDefaultsOnly, Category = GamePlay )
    TArray< FString > _gameFeaturesToEnable;

    UPROPERTY( EditDefaultsOnly, Category = GamePlay )
    TObjectPtr< const UMSPawnData > _defaultPawnData;

    UPROPERTY( EditDefaultsOnly, Instanced, Category = "Actions" )
    TArray< TObjectPtr< UGameFeatureAction > > _actions;

    UPROPERTY( EditDefaultsOnly, Category = GamePlay )
    TArray< TObjectPtr< UMSExperienceActionSet > > _actionsSets;

};
