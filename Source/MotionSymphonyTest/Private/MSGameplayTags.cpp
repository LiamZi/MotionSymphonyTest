// Fill out your copyright notice in the Description page of Project Settings.

#include "MSGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"
#include "MSLogChannels.h"

namespace MSGamplayTags {

UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_Move, "InputTag.Move", "Move input." );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_Look_Mouse, "InputTag.Look.Mouse",
                                "Look (mouse) input." );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_Look_Stick, "InputTag.Look.Stick",
                                "Look (stick) input." );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_Strafe, "Input.Strafe", "Strafe input." );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_Crouch, "InputTag.Crouch", "Crouch input." );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( InputTag_AutoRun, "InputTag.AutoRun", "Auto-run input." );

UE_DEFINE_GAMEPLAY_TAG_COMMENT( Movement_Mode_Walking, "Movement.Mode.Walking",
                                "Default Character movement tag" );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( Movement_Mode_NavWalking, "Movement.Mode.NavWalking",
                                "Default Character movement tag" );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( Movement_Mode_Falling, "Movement.Mode.Falling",
                                "Default Character movement tag" );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( Movement_Mode_Swimming, "Movement.Mode.Swimming",
                                "Default Character movement tag" );
UE_DEFINE_GAMEPLAY_TAG_COMMENT( Movement_Mode_Flying, "Movement.Mode.Flying",
                                "Default Character movement tag" );

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
    Movement_Mode_Custom, "Movement.Mode.Custom",
    "This is invalid and should be replaced with custom tags.  See "
    "LyraGameplayTags::CustomMovementModeTagMap." );

const TMap< uint8, FGameplayTag > MovementModeTagMap = {
    { MOVE_Walking, Movement_Mode_Walking },
    { MOVE_NavWalking, Movement_Mode_NavWalking },
    { MOVE_Falling, Movement_Mode_Falling },
    { MOVE_Swimming, Movement_Mode_Swimming },
    { MOVE_Flying, Movement_Mode_Flying },
    { MOVE_Custom, Movement_Mode_Custom }
};

const TMap< uint8, FGameplayTag > CustomMovementModeTagMap = {
    // Fill these in with your custom modes
};

FGameplayTag FindTagByString( const FString& str, bool isMatchPartialString ) {

    const auto& manager = UGameplayTagsManager::Get();
    auto        tag     = manager.RequestGameplayTag( FName( *str ), false );

    if ( !tag.IsValid() && isMatchPartialString ) {
        FGameplayTagContainer allTags;
        manager.RequestAllGameplayTags( allTags, true );

        for ( auto& t : allTags ) {
            if ( t.ToString().Contains( str ) ) {
                UE_LOG( LogMS, Display,
                        TEXT( "Could not find exact match for tag [%s] but found partial "
                              "match on tag [%s]." ),
                        *str, *t.ToString() );
                tag = t;
                break;
            }
        }
    }

    return tag;
}

};  // namespace MSGamplayTags
