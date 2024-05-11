// Fill out your copyright notice in the Description page of Project Settings.

#include "System/MSAssetManager.h"
#include "System/MSGameData.h"
#include "System/MSAssetManagerStartupJob.h"
#include "Engine/Engine.h"
#include "MSLogChannels.h"
#include "Misc/App.h"
#include "Misc/ScopedSlowTask.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(MSAssetManager)

const FName FMSBundles::Equipped( "Equipped" );

#define STARTUP_JOB_WEIGHTED( JobFunc, JobWeight )                            \
    _startupJobs.Add( FMSAssetManagerStartupJob(                               \
        #JobFunc,                                                             \
        [ this ]( const FMSAssetManagerStartupJob& StartupJob,                \
                  TSharedPtr< FStreamableHandle >& LoadHandle ) { JobFunc; }, \
        JobWeight ) )

#define STARTUP_JOB( JobFunc ) STARTUP_JOB_WEIGHTED( JobFunc, 1.f )


UMSAssetManager::UMSAssetManager() : _defaultPawnData{ nullptr } {}

UMSAssetManager& UMSAssetManager::Get() {
    check( GEngine );

    if ( UMSAssetManager* singleton = Cast< UMSAssetManager >( GEngine->AssetManager ) ) {
        return *singleton;
    }

    UE_LOG( LogMS, Fatal,
            TEXT( "Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set "
                  "to MSAssetManager!" ) );

    return *NewObject< UMSAssetManager >();
}

void UMSAssetManager::DumpLoadedAssets() {
    UE_LOG( LogMS, Log, TEXT( "========== Start Dumping Loaded Assets ==========" ) );

    for ( const UObject* LoadedAsset : Get()._loadedAssets ) {
        UE_LOG( LogMS, Log, TEXT( "  %s" ), *GetNameSafe( LoadedAsset ) );
    }

    UE_LOG( LogMS, Log, TEXT( "... %d assets in loaded pool" ),
            Get()._loadedAssets.Num() );
    UE_LOG( LogMS, Log, TEXT( "========== Finish Dumping Loaded Assets ==========" ) );
}

const UMSGameData& UMSAssetManager::GetGameData() {
    return GetOrLoadTypedGameData< UMSGameData >( _msGameDataPath );
}

const UMSPawnData* UMSAssetManager::GetDefaultPawnData() const {
    return GetAsset( _defaultPawnData );
}

UObject* UMSAssetManager::SynchronousLoadAsset( const FSoftObjectPath& assetPath ) {
    if ( assetPath.IsValid() ) {
        TUniquePtr< FScopeLogTime > logTimePtr;

        if ( ShouldLogAssetLoads() ) {
            logTimePtr = MakeUnique< FScopeLogTime >(
                *FString::Printf( TEXT( "Synchronously Load Asset [%s]" ),
                                  *assetPath.ToString() ),
                nullptr, FScopeLogTime::ScopeLog_Seconds );
        }

        if ( UAssetManager::IsInitialized() ) {
            return UAssetManager::GetStreamableManager().LoadSynchronous( assetPath,
                                                                          false );
        }

        return assetPath.TryLoad();
    }
    return nullptr;
}

bool UMSAssetManager::ShouldLogAssetLoads() {
    return FParse::Param( FCommandLine::Get(), TEXT( "LogAssetLoads" ) );
}

void UMSAssetManager::AddLoadedAsset( const UObject* asset ) {
    if ( ensureAlways( asset ) ) {
        FScopeLock loadedAssetLock( &_loadedAssetsCritical );
        _loadedAssets.Add( asset );
    }
}

void UMSAssetManager::StartInitialLoading() {
    SCOPED_BOOT_TIMING( "UMSAssetManager::StartInitialLoading" );

    Super::StartInitialLoading();

    STARTUP_JOB( InitializedGameplayCueManager() );

    { STARTUP_JOB_WEIGHTED( GetGameData(), 25.0f ); }

    DoAllStartupJobs();
}

void UMSAssetManager::PreBeginPIE( bool startSimulate ) {}

UPrimaryDataAsset* UMSAssetManager::LoadGameDataOfClass(
    TSubclassOf< UPrimaryDataAsset >           dataClass,
    const TSoftObjectPtr< UPrimaryDataAsset >& dataClassPath, FPrimaryAssetType type ) {
    return nullptr;
}

void UMSAssetManager::DoAllStartupJobs() {}

void UMSAssetManager::InitializedGameplayCueManager() {
    SCOPED_BOOT_TIMING( "UMSAssetManager::InitializeGameplayCueManager" );
   /* UMSGameplayCueManager* GCM = UMSGameplayCueManager::Get();
    check( GCM );
    GCM->LoadAlwaysLoadedCues();*/
}

void UMSAssetManager::UpdateInitializedGameContentLoadPercent(
    float gameContextPercent ) {}
