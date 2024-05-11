// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/MSGameMode.h"

#include "Developerments/MSDeveloperSettings.h"
#include "GameModes/MSExperienceDefinition.h"
#include "GameModes/MSExperienceManagerComponent.h"
#include "GameModes/MSWorldSettings.h"
#include "GameModes/MSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "MSLogChannels.h"
#include "System/MSAssetManager.h"

AMSGameMode::AMSGameMode( const FObjectInitializer& object ) : Super( object ) 
{
    GameStateClass = AMSGameState::StaticClass();

}

void AMSGameMode::InitGame( const FString& mapName, const FString& options,
                            FString& errorMessages ) {

    Super::InitGame( mapName, options, errorMessages );

    GetWorld()->GetTimerManager().SetTimerForNextTick(
        this, &AMSGameMode::HandleMatchAssignmentIfNotExpectingOne );
}

void AMSGameMode::InitGameState() {}

void AMSGameMode::HandleMatchAssignmentIfNotExpectingOne() {
    UE_LOG( LogMS, Warning, TEXT( "HandleMatchAssignmentIfNotExpectingOne" ) );

    FPrimaryAssetId experienceId;
    FString         experienceIdSource;

    UWorld* world = GetWorld();

    if ( !experienceId.IsValid()
         && UGameplayStatics::HasOption( OptionsString, TEXT( "Experience" ) ) ) {

        const auto experienceFromOptions =
            UGameplayStatics::ParseOption( OptionsString, TEXT( "Experience" ) );
        experienceId = FPrimaryAssetId(
            FPrimaryAssetType( UMSExperienceDefinition::StaticClass()->GetFName() ),
            FName( *experienceFromOptions ) );
        experienceIdSource = TEXT( "OptionsString" );
    }

    if ( !experienceId.IsValid() && world->IsPlayInEditor() ) {

        experienceId       = GetDefault< UMSDeveloperSettings >()->_experienceOverride;
        experienceIdSource = TEXT( "DeveloperSettings" );
    }

    if ( !experienceId.IsValid() ) {

        FString experienceFromCommandLine;
        if ( FParse::Value( FCommandLine::Get(), TEXT( "Experience=" ),
                            experienceFromCommandLine ) ) {
            experienceId = FPrimaryAssetId::ParseTypeAndName( experienceFromCommandLine );
            if ( !experienceId.PrimaryAssetType.IsValid() ) {
                experienceId = FPrimaryAssetId(
                    FPrimaryAssetType(
                        UMSExperienceDefinition::StaticClass()->GetFName() ),
                    FName( *experienceFromCommandLine ) );
                experienceIdSource = TEXT( "CommandLine" );
            }
        }
    }

    if ( !experienceId.IsValid() ) {

        if ( AMSWorldSettings* settings =
                 Cast< AMSWorldSettings >( GetWorldSettings() ) ) {
            experienceId       = settings->GetDefaultGameplayExperience();
            experienceIdSource = TEXT( "WorldSettings" );
        }
    }

    auto&      assetmanager = UMSAssetManager::Get();
    FAssetData dummy;
    if ( experienceId.IsValid()
         && !assetmanager.GetPrimaryAssetData( experienceId, dummy ) ) {
        UE_LOG( LogMSExperience, Error,
                TEXT( "EXPERIENCE: Wanted to use %s but couldn't find it, falling back "
                      "to the default)" ),
                *experienceId.ToString() );
        experienceId = FPrimaryAssetId();
    }

    if ( !experienceId.IsValid() ) {
        experienceId = FPrimaryAssetId( FPrimaryAssetType( "MSExperienceDefinition" ),
                                        FName( "BP_MSDefaultExperience" ) );
        experienceIdSource = TEXT( "Default" );
    }

    OnMatchAssignmentGiven( experienceId, experienceIdSource );
}

void AMSGameMode::OnMatchAssignmentGiven( FPrimaryAssetId experienceId,
                                          const FString&  experienceIdSource ) {
    if ( experienceId.IsValid() ) {
        UE_LOG( LogMSExperience, Log, TEXT( "Identified experience %s (Source: %s)" ),
                *experienceId.ToString(), *experienceIdSource );
           auto experienceComponent =
               GameState->FindComponentByClass< UMSExperienceManagerComponent >();
           check( experienceComponent );
           experienceComponent->SetCurrentExperience( experienceId );
    }
    else {
        UE_LOG(
            LogMSExperience, Error,
            TEXT(
                "Failed to identify experience, loading screen will stay up forever" ) );
    }
}
