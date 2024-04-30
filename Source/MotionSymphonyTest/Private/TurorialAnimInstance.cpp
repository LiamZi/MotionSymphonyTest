// Fill out your copyright notice in the Description page of Project Settings.

#include "TurorialAnimInstance.h"
#include "Objects/Assets/MotionMatchConfig.h"
#include "GameFramework/Character.h"
#include "Components/TrajectoryGenerator.h"
#include "Components/TrajectoryErrorWarping.h"
#include "Components/DistanceMatching.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/MMBlueprintFunctionLibrary.h"
#include "TurorialCharacter.h"

UTurorialAnimInstance::UTurorialAnimInstance()
    : _forcePoseSearch{false},
      _shouldMove{false},
      _isFalling{false},
      _hadMoveInputLastFrame{false},
      _hasMoveInput{false},
      _shouldBeIdle{true},
      _isStrafing{false},
      _lockFoot_L{false},
      _lockFoot_R{false},
      _heelHeight{false},
      _mmAnimData_NEUTRAL{nullptr},
      _mmAnimData_STRAFE{nullptr},
      _mmAnimConfig{nullptr},
      _character{nullptr},
      _movementComponent{nullptr},
      _trajectoryGenerator{nullptr},
      _distanceMatching{nullptr}
{
}

void UTurorialAnimInstance::SetupMotionMatching()
{
    auto actor = GetOwningActor();
    if (!IsValid(actor)) return;

    auto trajectory = actor->FindComponentByClass<UTrajectoryGenerator>();
    check(trajectory);

    _trajectoryGenerator = trajectory;

    auto distanceMatching = actor->FindComponentByClass<UDistanceMatching>();
    check(distanceMatching);

    _distanceMatching = distanceMatching;

    if (IsValid(trajectory))
    {
        trajectory->SetInputProfile(_mmInputProfile);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 5.f, FColor::Red,
            TEXT("Warning: MM Animation Blueprint - Could not set the input "
                 "profile on the trajectory generator as it is not valid. Are "
                 "you sure the character has a valid Trajectory Generator "
                 "Component added?"));
    }
}

void UTurorialAnimInstance::SetupMotionMatchingAndMode()
{
    SetupMotionMatching();
    SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);
}

void UTurorialAnimInstance::SetupCharcterMovent()
{
    auto actor = GetOwningActor();
    if (!IsValid(actor)) return;

    auto tc = Cast<ATurorialCharacter>(actor);

    _character = tc;
    _movementComponent = _character->GetCharacterMovement();
}

void UTurorialAnimInstance::SetupCharcterDetail()
{
    SetupCharcterMovent();
    SetupMotionMatchingAndMode();
}

void UTurorialAnimInstance::TickAnimation()
{
    if (!IsValid(_character))
    {
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error:
        // The Animation must need a character in this tick."));

        /*TArray<AActor *> outActors;
        UGameplayStatics::GetAllActorsOfClass(
            GetWorld(), ATurorialCharacter::StaticClass(), outActors);

        for (auto actor : outActors)
        {
            _character = Cast<ATurorialCharacter>(actor);
            if (_character)
            {
                break;
            }
            else
            {
                return;
            }
        }*/

        return;
    }

    SetIsFalling();
    SetMCVelocityAndGroundSpeed();
    TransitionInAndOutOfIdle();
    StrafingCheck();
    ConstructInputResponseData();
}

void UTurorialAnimInstance::TransitionInAndOutOfIdle()
{
    if (!_trajectoryGenerator) return;
    _hasMoveInput = _trajectoryGenerator->HasMoveInput();

    _shouldMove = (_groundSpeed > 10.0f);

    _shouldBeIdle = (!_shouldMove && !_hasMoveInput);

    if (_hasMoveInput != _hadMoveInputLastFrame)
    {
        _forcePoseSearch = true;
    }
}

void UTurorialAnimInstance::SetMCVelocityAndGroundSpeed()
{
    if (!_movementComponent)
    {
        _movementComponent = _character->GetCharacterMovement();
    }

    _velocity = _movementComponent->Velocity;
    _groundSpeed = UKismetMathLibrary::VSizeXY(_velocity);

    _hadMoveInputLastFrame = _hasMoveInput;

    _forcePoseSearch = false;
}

void UTurorialAnimInstance::SetIsFalling()
{
    if (!_movementComponent)
    {
        _movementComponent = _character->GetCharacterMovement();
    }

    _isFalling = _movementComponent->IsFalling();
}

void UTurorialAnimInstance::StrafingCheck()
{
    if (!_trajectoryGenerator) return;

    _isStrafing = (_trajectoryGenerator->TrajectoryBehaviour ==
                   ETrajectoryMoveMode::Strafe);
}

void UTurorialAnimInstance::ConstructInputResponseData()
{
    // if (_mmInputResponseData.DesiredInputArray.Num() <= 0 || !_character ||
    // !_mmAnimConfig)
    if (!_character || !_mmAnimConfig)
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 10.f, FColor::Red,
            TEXT("Error: The Animation must need a Input Response Data, "
                 "Character And a AnimConfig."));
        return;
    }

    UMMBlueprintFunctionLibrary::ConstructMotionInputFeatureArray(
        _mmInputResponseData, _character, _mmAnimConfig);
}

void UTurorialAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    auto actor = GetOwningActor();
    if (!IsValid(actor)) return;

    auto tc = Cast<ATurorialCharacter>(actor);
    if (!tc) return;

    _character = tc;
    _movementComponent = _character->GetCharacterMovement();
}

void UTurorialAnimInstance::NativeBeginPlay()
{
    Super::NativeInitializeAnimation();
    SetupCharcterDetail();
}

void UTurorialAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    TickAnimation();
}
