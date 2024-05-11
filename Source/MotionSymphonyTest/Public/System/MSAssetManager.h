// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Templates/SubclassOf.h"
#include "MSAssetManager.generated.h"

class UPrimaryDataAsset;
class UMSGameData;
class UMSPawnData;
struct FMSAssetManagerStartupJob;

struct FMSBundles {
    static const FName Equipped;
};
/**
 *
 */
UCLASS( Config = Game )
class MOTIONSYMPHONYTEST_API UMSAssetManager : public UAssetManager {
    GENERATED_BODY()

public:
    UMSAssetManager();

    static UMSAssetManager& Get();

    template < typename AssetType >
    static AssetType* GetAsset( const TSoftObjectPtr< AssetType >& assetPointer,
                                bool                               keepInMemory = true );

    template < typename AssetType >
    static TSubclassOf< AssetType >
    GetSubClass( const TSoftClassPtr< AssetType >& assetPointer,
                 bool                              keepInMemory = true );

    static void DumpLoadedAssets();

    const UMSGameData& GetGameData();
    const UMSPawnData* GetDefaultPawnData() const;

protected:
    template < typename GameDataClass >
    const GameDataClass&
    GetOrLoadTypedGameData( const TSoftObjectPtr< GameDataClass >& dataPath ) {
        if ( auto const result = _gameDataMap.Find( GameDataClass::StaticClass() ) ) {
            return *CastChecked< GameDataClass >( *result );
        }

        return *CastChecked< const GameDataClass >(
            LoadGameDataOfClass( GameDataClass::StaticClass(), dataPath,
                                 GameDataClass::StaticClass()->GetFName() ) );
    }

    static UObject* SynchronousLoadAsset( const FSoftObjectPath& assetPath );
    static bool     ShouldLogAssetLoads();

    void AddLoadedAsset( const UObject* asset );

    virtual void StartInitialLoading() override;

#if WITH_EDITOR
    virtual void PreBeginPIE( bool startSimulate ) override;
#endif  // WITH_EDITOR

    UPrimaryDataAsset*
    LoadGameDataOfClass( TSubclassOf< UPrimaryDataAsset >           dataClass,
                         const TSoftObjectPtr< UPrimaryDataAsset >& dataClassPath,
                         FPrimaryAssetType                          type );

private:
    void DoAllStartupJobs();
    void InitializedGameplayCueManager();
    void UpdateInitializedGameContentLoadPercent( float gameContextPercent );
    TArray< FMSAssetManagerStartupJob > _startupJobs;

protected:
    UPROPERTY( Transient )
    TMap< TObjectPtr< UClass >, TObjectPtr< UPrimaryDataAsset > > _gameDataMap;

    UPROPERTY( Config )
    TSoftObjectPtr< UMSGameData > _msGameDataPath;

    UPROPERTY( Config )
    TSoftObjectPtr< UMSPawnData > _defaultPawnData;

private:
    UPROPERTY()
    TSet< TObjectPtr< const UObject > > _loadedAssets;

    FCriticalSection _loadedAssetsCritical;
};

template < typename AssetType >
inline AssetType*
UMSAssetManager::GetAsset( const TSoftObjectPtr< AssetType >& assetPointer,
                           bool                               keepInMemory ) {
    return nullptr;
}

template < typename AssetType >
inline TSubclassOf< AssetType >
UMSAssetManager::GetSubClass( const TSoftClassPtr< AssetType >& assetPointer,
                              bool                              keepInMemory ) {
    return TSubclassOf< AssetType >();
}
