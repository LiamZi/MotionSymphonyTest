// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/MSGameplayCueManager.h"

#include "AbilitySystemGlobals.h"
#include "GameplayTagsManager.h"
#include "MSLogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MSGameplayCueManager)

const bool PreLoadEventInEditor = true;

UMSGameplayCueManager::UMSGameplayCueManager( const FObjectInitializer& object )
    : Super{ object } {}

UMSGameplayCueManager* UMSGameplayCueManager::Get() {
    return Cast< UMSGameplayCueManager >(
        UAbilitySystemGlobals::Get().GetGameplayCueManager() );
}

void UMSGameplayCueManager::OnCreated() {
    Super::OnCreated();

    UpdateDelayLoadDelegateListeners();
}

bool UMSGameplayCueManager::ShouldAsyncLoadRuntimeObjectLibraries() const {

    return false;
}

bool UMSGameplayCueManager::ShouldSyncLoadMissingGameplayCues() const {
    return false;
}

bool UMSGameplayCueManager::ShouldAsyncLoadMissingGameplayCues() const {
    return false;
}

void UMSGameplayCueManager::DumpGameplayCues( const TArray< FString >& Args ) {}

void UMSGameplayCueManager::LoadAlwaysLoadedCues() {
    //
    if ( ShouldDelayLoadGameplayCues() ) {
        auto&           tagManager = UGameplayTagsManager::Get();
        TArray< FName > additionalAlwaysLoadedCueTags;

        for ( const FName& name : additionalAlwaysLoadedCueTags ) {
            FGameplayTag tag = tagManager.RequestGameplayTag( name, false );
            if ( tag.IsValid() ) {
                ProcessTagToPreload( tag, nullptr );
            }
            else {
                UE_LOG( LogMS, Warning,
                        TEXT( "UMSGameplayCueManager::AdditionalAlwaysLoadedCueTags "
                              "contains invalid tag %s" ),
                        *tag.ToString() );

            }
        }
    }
}

void UMSGameplayCueManager::RefreshGameplayCuePrimaryAsset() {}

void UMSGameplayCueManager::OnGameplayTagLoaded( const FGameplayTag& tag ) {}

void UMSGameplayCueManager::HandlePostGarbageCollect() {}

void UMSGameplayCueManager::ProcessLoadedTags() {}

void UMSGameplayCueManager::ProcessTagToPreload( const FGameplayTag& Tag,
                                                 UObject*            OwningObject ) {}

void UMSGameplayCueManager::OnPreloadCueComplete( FSoftObjectPath           Path,
                                                  TWeakObjectPtr< UObject > OwningObject,
                                                  bool bAlwaysLoadedCue ) {}

void UMSGameplayCueManager::RegisterPreloadedCue( UClass*  LoadedGameplayCueClass,
                                                  UObject* OwningObject ) {}

void UMSGameplayCueManager::HandlePostLoadMap( UWorld* NewWorld ) {}

void UMSGameplayCueManager::UpdateDelayLoadDelegateListeners() {}

bool UMSGameplayCueManager::ShouldDelayLoadGameplayCues() const {
    return false;
}
