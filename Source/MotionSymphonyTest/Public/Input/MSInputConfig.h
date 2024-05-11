// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MSInputConfig.generated.h"

class UInputAction;
class UObject;
struct FFrame;

USTRUCT( BlueprintType )
struct FMSInputAction {
    GENERATED_BODY()

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    TObjectPtr< const UInputAction > _inputAction = nullptr;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta = ( Categories = "InputTag" ) )
    FGameplayTag _inputTag;
};

/**
 *
 */
UCLASS( BlueprintType, Const )
class MOTIONSYMPHONYTEST_API UMSInputConfig : public UDataAsset {
    GENERATED_BODY()

public:
    UMSInputConfig( const FObjectInitializer& obj );

    UFUNCTION( BlueprintCallable, Category = "MS|Pawn" )
    const UInputAction* FindNativeInputActionForTag( const FGameplayTag& tag,
                                                     bool logNotFound = true ) const;

    UFUNCTION( BlueprintCallable, Category = "MS|Pawn" )
    const UInputAction* FindAbilityInputActionForTag( const FGameplayTag& tag,
                                                      bool logNotFound = true ) const;

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly,
               meta = ( TitleProperty = "InputAction" ) )
    TArray< FMSInputAction > _abilityInputActions;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly,
               meta = ( TitleProperty = "InputAction" ) )
    TArray< FMSInputAction > _nativeInputActions;
};
