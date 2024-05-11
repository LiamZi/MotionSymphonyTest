// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/MSExperienceDefinition.h"

#include "Characters/MSPawnData.h"
#include "GameFeatureAction.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#define LOCTEXT_NAMESPACE "MSSystem"

UMSExperienceDefinition::UMSExperienceDefinition() {}

#if WITH_EDITOR
EDataValidationResult
UMSExperienceDefinition::IsDataValid( FDataValidationContext& context ) const {

    auto  result = CombineDataValidationResults( Super::IsDataValid( context ),
                                                 EDataValidationResult::Valid );
    int32 index  = 0;

    for ( const auto& a : _actions ) {

        if ( a ) {
            auto childResult = a->IsDataValid( context );
            result           = CombineDataValidationResults( result, childResult );
        }
        else {
            result = EDataValidationResult::Invalid;
            context.AddError( FText::Format(
                LOCTEXT( "ActionEntryIsNull", "Null entry at index {0} in Actions" ),
                FText::AsNumber( index ) ) );
        }

        ++index;
    }

    if ( !GetClass()->IsNative() ) {
        auto parent = GetClass()->GetSuperClass();

        const UClass* firstNativeParent = parent;
        while ( ( firstNativeParent != nullptr ) && !firstNativeParent->IsNative() ) {
            firstNativeParent = firstNativeParent->GetSuperClass();
        }

        if ( firstNativeParent != parent ) {
            context.AddError( FText::Format(
                LOCTEXT( "ExperienceInheritenceIsUnsupported",
                         "Blueprint subclasses of Blueprint experiences is not currently "
                         "supported (use composition via ActionSets instead). Parent "
                         "class was {0} but should be {1}." ),
                FText::AsCultureInvariant( GetPathNameSafe( parent ) ),
                FText::AsCultureInvariant( GetPathNameSafe( firstNativeParent ) ) ) );
            result = EDataValidationResult::Invalid;
        }
    }

    return result;
}
#endif

#if WITH_EDITORONLY_DATA
void UMSExperienceDefinition::UpdateAssetBundleData() {

    Super::UpdateAssetBundleData();

    for (auto &a : _actions)
    {
        if ( !a )
            continue;

        a->AddAdditionalAssetBundleData( AssetBundleData );
    }
}
#endif


#undef LOCTEXT_NAMESPACE