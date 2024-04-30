// Fill out your copyright notice in the Description page of Project Settings.

#include "TurorialCharacter.h"
#include "TurorialPlayerController.h"
#include "Components/TrajectoryGenerator.h"
#include "Components/TrajectoryErrorWarping.h"
#include "Components/DistanceMatching.h"
#include "Components/CapsuleComponent.h"
#include "Enumerations/EMotionMatchingEnums.h"
#include "BlueprintGameplayTagLibrary.h"
#include "Utility/MMBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "TurorialPlayerController.h"

// Sets default values
ATurorialCharacter::ATurorialCharacter()
    : _overrideQualityVsResponsiveness{0.5f},
      _inputMapping{nullptr},
      _neutralCalibration{nullptr},
      _strafeCalibration{nullptr},
      _useRootMotion{false},
      _cameraBoom{nullptr},
      _followCamera{nullptr},
      _trajectoryGenerator{nullptr},
      _trajectoryErrorWarping{nullptr},
      _distanceMatching{nullptr}
{
    // Set this character to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    auto characterMovement = GetCharacterMovement();
    characterMovement->bOrientRotationToMovement = true;
    characterMovement->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    characterMovement->JumpZVelocity = 700.f;
    characterMovement->AirControl = 0.35f;
    characterMovement->MaxWalkSpeed = 500.f;
    characterMovement->MinAnalogWalkSpeed = 20.f;
    characterMovement->BrakingDecelerationWalking = 2000.f;
    characterMovement->BrakingDecelerationFalling = 1500.0f;

    _cameraBoom =
        CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    _cameraBoom->SetupAttachment(RootComponent);
    _cameraBoom->TargetArmLength = 400.0f;
    _cameraBoom->bUsePawnControlRotation = true;

    _followCamera =
        CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    _followCamera->SetupAttachment(
        _cameraBoom,
        USpringArmComponent::SocketName); // Attach the camera to the end of the
                                          // boom and let the boom adjust to
                                          // match the controller orientation
    _followCamera->bUsePawnControlRotation = false;

    _trajectoryGenerator = CreateDefaultSubobject<UTrajectoryGenerator>(
        TEXT("TestTrajectoryGenerator"));
    _trajectoryErrorWarping = CreateDefaultSubobject<UTrajectoryErrorWarping>(
        TEXT("TestTrajectoryErrorWarping"));
    _trajectoryErrorWarping->WarpMode = ETrajectoryErrorWarpMode::Standard;
    _trajectoryErrorWarping->WarpRate = 60.0f;
    _trajectoryErrorWarping->MinTrajectoryLength = 50.0f;
    _trajectoryErrorWarping->ErrorActivationRange = FVector2D(0.25f, 30.0f);
    _distanceMatching =
        CreateDefaultSubobject<UDistanceMatching>(TEXT("TestDistanceMatching"));
}

// Called when the game starts or when spawned
void ATurorialCharacter::BeginPlay()
{
    Super::BeginPlay();

    BeginNeutral();
    BeginRun();
}

void ATurorialCharacter::BeginNeutral()
{
    auto neutralTag = UGameplayTagsManager::Get().RequestGameplayTag(
        TEXT("Motion.Sytle.Neutral"));
    SetStyleTag(neutralTag);
    _trajectoryGenerator->TrajectoryBehaviour = ETrajectoryMoveMode::Standard;
    _trajectoryErrorWarping->SetMode(ETrajectoryErrorWarpMode::Standard, 60.0f,
                                     50.0f, 0.25f, 30.0f);
}

void ATurorialCharacter::BeginRun()
{
    SetSpeedTag(UGameplayTagsManager::Get().RequestGameplayTag(
        TEXT("Motion.Speed.Run")));
    if (_trajectoryGenerator)
    {
        _trajectoryGenerator->MaxSpeed = 475.0f;
        _trajectoryGenerator->MoveResponse = 8.0f;
        _trajectoryGenerator->TurnResponse = 12.0f;
    }

    _overrideQualityVsResponsiveness = 0.5f;

    _neutralCalibration = nullptr;
}

void ATurorialCharacter::BeginWalk()
{
    SetSpeedTag(UGameplayTagsManager::Get().RequestGameplayTag(
        TEXT("Motion.Speed.Walk")));
    if (_trajectoryGenerator)
    {
        _trajectoryGenerator->MaxSpeed = 215.0f;
        _trajectoryGenerator->MoveResponse = 9.0f;
        _trajectoryGenerator->TurnResponse = 8.0f;
    }

    _overrideQualityVsResponsiveness = 0.5f;

    //_neutralCalibration = nullptr;
}

void ATurorialCharacter::BeginSprint()
{
    auto strafeTag = UGameplayTagsManager::Get().RequestGameplayTag(
        TEXT("Motion.Sytle.Strafe"));
    if (_styleTag != strafeTag)
    {
        auto sprintTag = UGameplayTagsManager::Get().RequestGameplayTag(
            TEXT("Motion.Speed.Sprint"));
        SetSpeedTag(sprintTag);

        if (_trajectoryGenerator)
        {
            _trajectoryGenerator->MaxSpeed = 650.0f;
            _trajectoryGenerator->MoveResponse = 6.0f;
            _trajectoryGenerator->TurnResponse = 10.0f;
        }

        _overrideQualityVsResponsiveness = 0.45f;

        _neutralCalibration = nullptr;
    }
}

void ATurorialCharacter::BeginStrafe()
{
    auto strafeTag = UGameplayTagsManager::Get().RequestGameplayTag(
        TEXT("Motion.Sytle.Strafe"));
    SetStyleTag(strafeTag);

    if (_speedTag == UGameplayTagsManager::Get().RequestGameplayTag(
                         TEXT("Motion.Speed.Sprint")))
    {
        BeginRun();
    }

    if (_trajectoryGenerator)
    {
        _trajectoryGenerator->TrajectoryBehaviour = ETrajectoryMoveMode::Strafe;
    }

    if (_trajectoryErrorWarping)
    {
        _trajectoryErrorWarping->SetMode(ETrajectoryErrorWarpMode::Strafe,
                                         90.0f, 50.0f, 2.0f, 180.0f);
    }
}

void ATurorialCharacter::RemoveInputMapping(AController* pc)
{
    UE_LOG(LogTemp, Warning, TEXT("RemoveInputMapping"));
    if (!IsValid(pc)) return;

    if (!pc->IsLocalPlayerController()) return;

    auto c = Cast<ATurorialPlayerController>(pc);
    auto subSystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            c->GetLocalPlayer());
    if (!IsValid(subSystem)) return;

    subSystem->RemoveMappingContext(_inputMapping);
}

void ATurorialCharacter::AddInputMapping(AController* pc)
{
    UE_LOG(LogTemp, Warning, TEXT("AddInputMapping"));
    if (!IsValid(pc)) return;

    if (pc->IsLocalPlayerController())
    {
        auto c = Cast<ATurorialPlayerController>(pc);
        auto subSystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                c->GetLocalPlayer());
        if (!IsValid(subSystem)) return;
        subSystem->AddMappingContext(_inputMapping, 0);
    }
}

const void ATurorialCharacter::SetUseRootMotion(bool isUsed)
{
    _useRootMotion = isUsed;
}

bool ATurorialCharacter::GetUseRootMotion() const { return _useRootMotion; }

const void ATurorialCharacter::SetLastFrameRotation(FRotator rotation)
{
    _lastFrameRotation = rotation;
}

FRotator ATurorialCharacter::GetLastFrameRotation() const
{
    return _lastFrameRotation;
}

void ATurorialCharacter::OnSetTrajectoryInputVector_Multicast_Implementation(
    float x, float y)
{
    auto isLocally = IsLocallyControlled();
    if (isLocally) return;

    if (!_trajectoryGenerator) return;
    _trajectoryGenerator->SetTrajectoryInput(x, y);
}

void ATurorialCharacter::SetStyleTag(FGameplayTag tag)
{
    UBlueprintGameplayTagLibrary::RemoveGameplayTag(_locomotionTags, _styleTag);
    _styleTag = tag;

    UBlueprintGameplayTagLibrary::AddGameplayTag(_locomotionTags, _styleTag);
}

void ATurorialCharacter::SetSpeedTag(FGameplayTag tag)
{
    UE_LOG(LogTemp, Warning, TEXT("Set Speed Tag %s"),
           *(tag.GetTagName().ToString()));

    UBlueprintGameplayTagLibrary::RemoveGameplayTag(_locomotionTags, _speedTag);
    _speedTag = tag;
    UBlueprintGameplayTagLibrary::AddGameplayTag(_locomotionTags, _speedTag);
}

// Called every frame
void ATurorialCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ApplyTrajectoryErrorWarping(DeltaTime);
    SetStrafeDirectionFromCamera();
    SetRootMotionState();
}

// Called to bind functionality to input
void ATurorialCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    auto pc = Cast<ATurorialPlayerController>(GetController());
    if (pc != nullptr && pc->IsLocalPlayerController())
    {
        auto subSystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                pc->GetLocalPlayer());
        subSystem->ClearAllMappings();
        subSystem->AddMappingContext(_inputMapping, 0);

        pc->SetupPlayerInputComponent(PlayerInputComponent);
    }
}

void ATurorialCharacter::Move(FVector2D inputVector)
{
    auto cameraComponent = this->FindComponentByClass<UCameraComponent>();
    if (!cameraComponent) return;

    auto vec = UMMBlueprintFunctionLibrary::GetVectorRelativeToCamera(
        inputVector.Y, inputVector.X, cameraComponent);
    AddMovementInput(vec);
    if (!_trajectoryGenerator) return;
    _trajectoryGenerator->SetTrajectoryInput(vec.X, vec.Y);
}

void ATurorialCharacter::EnbleRootMotion()
{
    auto animInstance = GetMesh()->GetAnimInstance();
    if (!IsValid(animInstance)) return;

    animInstance->SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);

    _useRootMotion = true;
}

void ATurorialCharacter::DisableRootMotion()
{
    auto animInstance = GetMesh()->GetAnimInstance();
    if (!IsValid(animInstance)) return;

    animInstance->SetRootMotionMode(
        ERootMotionMode::RootMotionFromMontagesOnly);
    _useRootMotion = false;
}

FRotator ATurorialCharacter::UndoModelRotation()
{
    auto mesh = GetMesh();
    if (!IsValid(mesh)) return FRotator();

    auto r = GetActorRotation();
    auto normalizedRotation =
        UKismetMathLibrary::NormalizedDeltaRotator(r, _lastFrameRotation);
    auto yawRotation =
        UKismetMathLibrary::MakeRotator(0.0f, 0.0f, normalizedRotation.Yaw);
    auto invertRotator = UKismetMathLibrary::NegateRotator(yawRotation);

    mesh->AddLocalRotation(invertRotator);

    _lastFrameRotation = GetActorRotation();

    return _lastFrameRotation;
}

const FGameplayTag& ATurorialCharacter::GetSpeedTag() const
{
    return _speedTag;
}

const FGameplayTag& ATurorialCharacter::GetStyleTag() const
{
    return _styleTag;
}

void ATurorialCharacter::ApplyTrajectoryErrorWarping(float deltaTime)
{
    if (!_trajectoryGenerator || !_trajectoryErrorWarping) return;

    auto hasMoveInput = _trajectoryGenerator->HasMoveInput();
    if (!hasMoveInput) return;

    _trajectoryErrorWarping->ApplyTrajectoryErrorWarping(deltaTime, 1.0f);
}

void ATurorialCharacter::SetStrafeDirectionFromCamera()
{
    if (!_trajectoryGenerator) return;

    if (!(_trajectoryGenerator->TrajectoryBehaviour ==
          ETrajectoryMoveMode::Strafe))
        return;

    if (!_followCamera) return;

    _trajectoryGenerator->StrafeDirection = _followCamera->GetForwardVector();
    _trajectoryGenerator->StrafeDirection.Z = 0.0f;

    _trajectoryGenerator->StrafeDirection.Normalize();
}

void ATurorialCharacter::SetRootMotionState()
{
    auto isFalling = GetCharacterMovement()->IsFalling();
    if (_useRootMotion)
    {
        if (!isFalling) return;

        DisableRootMotion();
    }
    else
    {
        if (isFalling) return;
        EnbleRootMotion();
    }
}
