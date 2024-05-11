// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/MSExperienceManagerComponent.h"

#include "GameModes/MSExperienceDefinition.h"
#include "GameModes/MSExperienceActionSet.h"
#include "MSLogChannels.h"
#include "System/MSAssetManager.h"

UMSExperienceManagerComponent::UMSExperienceManagerComponent(
    const FObjectInitializer& object )
    : Super( object ) {
    SetIsReplicatedByDefault( true );
}

void UMSExperienceManagerComponent::EndPlay( const EEndPlayReason::Type reason ) {

    Super::EndPlay( reason );
}

void UMSExperienceManagerComponent::SetCurrentExperience( FPrimaryAssetId id ) {

    auto& assetManager = UMSAssetManager::Get();
    auto  assetPath    = assetManager.GetPrimaryAssetPath( id );
    TSubclassOf< UMSExperienceDefinition > assetClass =
        Cast< UClass >( assetPath.TryLoad() );
    check( assetClass );

    const auto* experience = GetDefault< UMSExperienceDefinition >( assetClass );
    check( experience != nullptr );
    check( _currentExperience == nullptr );
    _currentExperience = experience;

    StartExperienceLoad();
}

void UMSExperienceManagerComponent::StartExperienceLoad() {

    check( _currentExperience != nullptr );
    check( _loadState == EMSExperienceLoadState::UnLoaded );

    UE_LOG( LogMSExperience, Log,
            TEXT( "EXPERIENCE: StartExperienceLoad(CurrentExperience = %s, %s)" ),
            *_currentExperience->GetPrimaryAssetId().ToString(), TEXT( "" ) );

    _loadState = EMSExperienceLoadState::Loading;

    auto& assetManager = UMSAssetManager::Get();

    TSet< FPrimaryAssetId > bundleAssetList;
    TSet< FSoftObjectPath > rawAssetList;

    bundleAssetList.Add( _currentExperience->GetPrimaryAssetId() );
    for (const auto& actionSet : _currentExperience->_actionsSets)
    {
        if ( !actionSet )
            continue;

        bundleAssetList.Add( actionSet->GetPrimaryAssetId() );
    }

    TArray< FName > bundlesToLoad;
    bundlesToLoad.Add( FMSBundles::Equipped );

}
