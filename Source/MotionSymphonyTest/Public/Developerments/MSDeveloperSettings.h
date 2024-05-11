// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/PrimaryAssetId.h"
#include "UObject/SoftObjectPath.h"

#include "MSDeveloperSettings.generated.h"


/**
 *
 */
//UCLASS( config = EditorPerProjectUserSettings, MinimalAPI )
UCLASS( config = EditorPerProjectUserSettings )
class MOTIONSYMPHONYTEST_API UMSDeveloperSettings : public UDeveloperSettingsBackedByCVars {
    GENERATED_BODY()

public:
    UMSDeveloperSettings();
    virtual FName GetCategoryName() const override;

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Config, Category = MS, meta = ( AllowTypes = "MSExperienceDefinition" ) )
    FPrimaryAssetId _experienceOverride;
};
