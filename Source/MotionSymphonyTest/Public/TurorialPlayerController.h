// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TurorialPlayerController.generated.h"

class UInputDataConfig;
class ATurorialCharacter;
class FExec;

/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API ATurorialPlayerController
    : public APlayerController
{
    GENERATED_BODY()

public:
    ATurorialPlayerController();

    void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
    virtual void OnPossess(APawn* aPawn) override;

private:
    void Move(const FInputActionValue& value);
    void Look(const FInputActionValue& value);
    void Jump();
    void Walk();
    void SprintStarted();
    void SprintEnded();
    void StrafeStarted();
    void StrafeEnded();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    UInputDataConfig* _inputActions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool _isBaseSpeedWalk;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    ATurorialCharacter* _character;
};
