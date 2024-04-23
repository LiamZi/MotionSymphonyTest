// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagsClasses.h"

#include "TurorialCharacter.generated.h"


class UInputMappingContext;
class UTrajectoryGenerator;
class UTrajectoryErrorWarping;
class UDistanceMatching;

UCLASS()
class MOTIONSYMPHONYTEST_API ATurorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurorialCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BeginNeutral();

	UFUNCTION(BlueprintCallable, Category = "Locomotion Tag Management")
	void SetStyleTag(FGameplayTag tag);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* _inputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Tags")
	FGameplayTag _styleTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UTrajectoryGenerator *_trajectoryGenerator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UTrajectoryErrorWarping* _trajectoryErrorWarping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	UDistanceMatching* _distanceMatching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Tags")
	FGameplayTagContainer _locomotionTags;
};
