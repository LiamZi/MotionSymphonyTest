// Fill out your copyright notice in the Description page of Project Settings.


#include "MSLogChannels.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY( LogMS );
DEFINE_LOG_CATEGORY( LogMSExperience );
DEFINE_LOG_CATEGORY( LogMSAbilitySystem );
DEFINE_LOG_CATEGORY( LogMSTeams );

MOTIONSYMPHONYTEST_API FString GetClientServerContextString( UObject* ContextObject ) {

    return TEXT("[]");
}
