// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "MSGameplayCueManager.generated.h"

/**
 *
 */
UCLASS()
class MOTIONSYMPHONYTEST_API UMSGameplayCueManager : public UGameplayCueManager {
    GENERATED_BODY()

public:
    UMSGameplayCueManager( const FObjectInitializer& object = FObjectInitializer::Get() );

    static UMSGameplayCueManager* Get();

    virtual void OnCreated() override;
    virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const override;
    virtual bool ShouldSyncLoadMissingGameplayCues() const override;
    virtual bool ShouldAsyncLoadMissingGameplayCues() const override;

    static void DumpGameplayCues( const TArray< FString >& Args );
    void        LoadAlwaysLoadedCues();
    void        RefreshGameplayCuePrimaryAsset();

private:
    void OnGameplayTagLoaded( const FGameplayTag& tag );
    void HandlePostGarbageCollect();
    void ProcessLoadedTags();
    void ProcessTagToPreload( const FGameplayTag& Tag, UObject* OwningObject );
    void OnPreloadCueComplete( FSoftObjectPath           Path,
                               TWeakObjectPtr< UObject > OwningObject,
                               bool                      bAlwaysLoadedCue );
    void RegisterPreloadedCue( UClass* LoadedGameplayCueClass, UObject* OwningObject );
    void HandlePostLoadMap( UWorld* NewWorld );
    void UpdateDelayLoadDelegateListeners();
    bool ShouldDelayLoadGameplayCues() const;

private:
    struct FLoadedGameplayTagToProcessData
    {
        FGameplayTag _Tag;
        TWeakObjectPtr< UObject > _WeakOwner;
        FLoadedGameplayTagToProcessData() {}

        FLoadedGameplayTagToProcessData( const FGameplayTag&              tag,
                                         const TWeakObjectPtr< UObject >& weakOwner )
            : _Tag{ tag }, _WeakOwner{ weakOwner } {}
    };

private:
    UPROPERTY( Transient )
    TSet< TObjectPtr< UClass > >           _preLoadedCues;
    TMap< FObjectKey, TSet< FObjectKey > > _preLoadedCueReferencers;

    UPROPERTY( Transient )
    TSet< TObjectPtr< UClass > > _alwaysLoadedCues;

    TArray< FLoadedGameplayTagToProcessData > _loadedGameplayTagsToProcess;
    FCriticalSection                          _loadedGameplayTagsToProcessCS;
    bool                                      _isProcessLoadedTagsAfterGC = false;
};
