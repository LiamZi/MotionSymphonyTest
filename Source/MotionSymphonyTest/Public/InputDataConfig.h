// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

class UInputAction;

/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API UInputDataConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _move;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _look;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _jump;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _walk;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _sprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* _strafe;
};
