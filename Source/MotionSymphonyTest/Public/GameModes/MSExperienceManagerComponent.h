// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameStateComponent.h"
#include "CoreMinimal.h"
#include "MSExperienceManagerComponent.generated.h"

class UMSExperienceDefinition;

enum class EMSExperienceLoadState {
    UnLoaded,
    Loading,
    LoadingGameFeatures,
    LoadingChaosTestingDelay,
    ExecutingActions,
    Loaded,
    Deactiving
};

/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API UMSExperienceManagerComponent : public UGameStateComponent {
    GENERATED_BODY()

public:
    UMSExperienceManagerComponent(
        const FObjectInitializer& object = FObjectInitializer::Get() );

    virtual void EndPlay( const EEndPlayReason::Type reason ) override;

    void SetCurrentExperience( FPrimaryAssetId id );

private:
    void StartExperienceLoad();

private:
    // UPROPERTY( ReplicatedUsing = OnRep_CurrentExperience )
    UPROPERTY()
    TObjectPtr< const UMSExperienceDefinition > _currentExperience;
    EMSExperienceLoadState _loadState = EMSExperienceLoadState::UnLoaded;
};
