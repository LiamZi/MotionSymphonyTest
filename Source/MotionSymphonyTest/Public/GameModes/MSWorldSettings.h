// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MSWorldSettings.generated.h"

class UMSExperienceDefinition;
/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API AMSWorldSettings : public AWorldSettings {
    GENERATED_BODY()

public:
    AMSWorldSettings(const FObjectInitializer &object);

#if WITH_EDITOR
    virtual void CheckForErrors() override;
#endif

    FPrimaryAssetId GetDefaultGameplayExperience() const;

};
