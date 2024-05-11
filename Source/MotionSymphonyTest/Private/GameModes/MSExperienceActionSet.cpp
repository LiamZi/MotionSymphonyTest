// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/MSExperienceActionSet.h"

#include "GameFeatureAction.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(MSExperienceActionSet)

#define LOCTEXT_NAMESPACE "LyraSystem"

UMSExperienceActionSet::UMSExperienceActionSet() {}

#if WITH_EDITOR
EDataValidationResult
UMSExperienceActionSet::IsDataValid( FDataValidationContext& context ) const {

    auto result = CombineDataValidationResults( Super::IsDataValid( context ),
                                                EDataValidationResult::Valid );

    int32 index = 0;

    for ( const auto& action : _actions ) {
        if ( action ) {
            auto child = action->IsDataValid( context );
            result     = CombineDataValidationResults( result, child );
        }
        else {
            result = EDataValidationResult::Invalid;
            context.AddError( FText::Format(
                LOCTEXT( "ActionEntryIsNull", "Null entry at index {0} in Actions" ),
                FText::AsNumber( index ) ) );
        }
        ++index;
    }
    return result;
}
#endif

#if WITH_EDITORONLY_DATA
void UMSExperienceActionSet::UpdateAssetBundleData() {
    Super::UpdateAssetBundleData();

    for ( auto& a : _actions ) {
        if ( !a )
            continue;

        a->AddAdditionalAssetBundleData( AssetBundleData );
    }
}
#endif
