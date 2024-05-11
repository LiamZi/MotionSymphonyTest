// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "UObject/NoExportTypes.h"



#include "MSGameMode.generated.h"


/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API AMSGameMode : public AModularGameModeBase {
    GENERATED_BODY()

public:
    AMSGameMode( const FObjectInitializer& object = FObjectInitializer::Get() );

    virtual void InitGame( const FString& mapName, const FString& options, FString& errorMessages ) override;
    virtual void InitGameState() override;

protected:
    void HandleMatchAssignmentIfNotExpectingOne();
    void OnMatchAssignmentGiven( FPrimaryAssetId experienceId, const FString& experienceIdSource );
};
