// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagsClasses.h"
#include "Objects/Assets/MotionCalibration.h"
#include "TurorialCharacter.generated.h"


class UInputMappingContext;
class UTrajectoryGenerator;
class UTrajectoryErrorWarping;
class UDistanceMatching;
class UMotionCalibration;

UCLASS()
class MOTIONSYMPHONYTEST_API ATurorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurorialCharacter();

	UFUNCTION(BlueprintCallable)
	void BeginNeutral();

	UFUNCTION(BlueprintCallable)
	void BeginRun();

	UFUNCTION(BlueprintCallable)
	void BeginWalk();

	UFUNCTION(BlueprintCallable)
	void BeginSprint();

	UFUNCTION(BlueprintCallable)
	void BeginStrafe();

	UFUNCTION(BlueprintCallable)
	void RemoveInputMapping(AController* pc);

	UFUNCTION(BlueprintCallable)
	void AddInputMapping(AController* pc);

	UFUNCTION(BlueprintCallable)
	const void SetUseRootMotion(bool isUsed);

	UFUNCTION(BlueprintPure)
	bool GetUseRootMotion() const;

	UFUNCTION(BlueprintCallable)
	const void SetLastFrameRotation(FRotator rotation);

	UFUNCTION(BlueprintPure)
	FRotator GetLastFrameRotation() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetTrajectoryInputVector_Multicast(float x, float y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Locomotion Tag Management")
	void SetStyleTag(FGameplayTag tag);

	UFUNCTION(BlueprintCallable, Category = "Locomotion Tag Management")
	void SetSpeedTag(FGameplayTag tag);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Move(FVector2D inputVector);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return _cameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return _followCamera; }

	UFUNCTION(BlueprintCallable, Category = "Root Motion")
	void EnbleRootMotion();

	UFUNCTION(BlueprintCallable, Category = "Root Motion")
	void DisableRootMotion();

	UFUNCTION(BlueprintCallable, Category = "Experimental")
	FRotator UndoModelRotation();

private:
	void ApplyTrajectoryErrorWarping(float deltaTime);
	void SetStrafeDirectionFromCamera();
	void SetRootMotionState();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* _inputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Tags")
	FGameplayTag _styleTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Tags")
	FGameplayTag _speedTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UTrajectoryGenerator *_trajectoryGenerator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UTrajectoryErrorWarping* _trajectoryErrorWarping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UDistanceMatching* _distanceMatching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Tags")
	FGameplayTagContainer _locomotionTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Matching")
	float _overrideQualityVsResponsiveness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Matching")
	UMotionCalibration *_neutralCalibration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Matching")
	UMotionCalibration *_strafeCalibration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* _cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* _followCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool _useRootMotion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator _lastFrameRotation;
	
};
