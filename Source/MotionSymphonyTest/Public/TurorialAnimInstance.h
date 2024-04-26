// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/InputProfile.h"
#include "Data/Trajectory.h"
#include "TurorialAnimInstance.generated.h"

/**
 *
 */

class UTrajectoryGenerator;
class UTrajectoryErrorWarping;
class UDistanceMatching;
class UMotionCalibration;
class UMotionDataAsset;
class UMotionMatchConfig;
class ATurorialCharacter;
class UCharacterMovementComponent;

UCLASS()
class MOTIONSYMPHONYTEST_API UTurorialAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UTurorialAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "Motion Matching")
	void SetupMotionMatching();

	UFUNCTION(BlueprintCallable, Category = "Setup Character")
	void SetupMotionMatchingAndMode();

	UFUNCTION(BlueprintCallable, Category = "Setup Character")
	void SetupCharcterMovent();

	UFUNCTION(BlueprintCallable, Category = "Setup Character")
	void SetupCharcterDetail();

	UFUNCTION(BlueprintCallable, Category = "Tick Anim")
	void TickAnimation();

	UFUNCTION(BlueprintCallable, Category = "Tick Anim")
	void TransitionInAndOutOfIdle();

	UFUNCTION(BlueprintCallable, Category = "Tick Anim")
	void StrafingCheck();

	UFUNCTION(BlueprintCallable, Category = "Tick Anim")
	void ConstructInputResponseData();


private:
	void SetMCVelocityAndGroundSpeed();
	void SetIsFalling();
	


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	FVector _velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	float _groundSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _shouldMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _isFalling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _hadMoveInputLastFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _hasMoveInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _shouldBeIdle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LocomotionState")
	bool _isStrafing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FootLocking")
	bool _lockFoot_L;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FootLocking")
	bool _lockFoot_R;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IK")
	float _heelHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	UMotionDataAsset* _mmAnimData_NEUTRAL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	UMotionDataAsset* _mmAnimData_STRAFE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	FInputProfile _mmInputProfile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	FMotionMatchingInputData _mmInputResponseData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	UMotionMatchConfig* _mmAnimConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MotionMatching")
	bool _forcePoseSearch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	ATurorialCharacter* _character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	UCharacterMovementComponent* _movementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	UTrajectoryGenerator* _trajectoryGenerator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	UDistanceMatching* _distanceMatching;


};
