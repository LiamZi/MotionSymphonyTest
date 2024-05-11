// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 *
 */

namespace MSGameplayTags {

MOTIONSYMPHONY_API FGameplayTag FindTagByString( const FString& str,
                                                 bool isMatchPartialString = false );

MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_Walking );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_NavWalking );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_Falling );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_Swimming );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_Flying );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( Movement_Mode_Custom );

MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_Move );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_Look_Mouse );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_Look_Stick );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_Crouch );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_AutoRun );
MOTIONSYMPHONY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( InputTag_Strafe );


};  // namespace MSGameplayTags