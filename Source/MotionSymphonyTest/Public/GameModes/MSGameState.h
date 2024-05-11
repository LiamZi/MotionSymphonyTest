// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "MSGameState.generated.h"


class UMSExperienceManagerComponent;
/**
 *
 */
UCLASS( Config = Game )
class MOTIONSYMPHONYTEST_API AMSGameState : public AModularGameStateBase {
    GENERATED_BODY()

public:
    AMSGameState( const FObjectInitializer& object = FObjectInitializer::Get() );

    virtual void PreInitializeComponents() override;
    virtual void PostInitializeComponents() override;
    virtual void EndPlay( const EEndPlayReason::Type reason ) override;
    virtual void Tick( float deltaSeconds ) override;

    virtual void AddPlayerState( APlayerState* state ) override;
    virtual void RemovePlayerState( APlayerState* state ) override;
    virtual void SeamlessTravelTransitionCheckpoint( bool isTransitionMap ) override;

private:
    UPROPERTY()
    TObjectPtr< UMSExperienceManagerComponent > _experienceManagerComponent;
};
