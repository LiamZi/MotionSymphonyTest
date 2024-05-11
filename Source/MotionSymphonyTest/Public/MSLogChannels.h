// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

class UObject;


MOTIONSYMPHONYTEST_API DECLARE_LOG_CATEGORY_EXTERN( LogMS, Log, All );
MOTIONSYMPHONYTEST_API DECLARE_LOG_CATEGORY_EXTERN( LogMSExperience, Log, All );
MOTIONSYMPHONYTEST_API DECLARE_LOG_CATEGORY_EXTERN( LogMSAbilitySystem, Log, All );
MOTIONSYMPHONYTEST_API DECLARE_LOG_CATEGORY_EXTERN( LogMSTeams, Log, All );

MOTIONSYMPHONYTEST_API FString GetClientServerContextString( UObject* ContextObject = nullptr );