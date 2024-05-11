// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/MSInputConfig.h"

#include "MSLogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MSInputConfig)

 UMSInputConfig::UMSInputConfig( const FObjectInitializer& obj ) {}

 const UInputAction*
 UMSInputConfig::FindNativeInputActionForTag( const FGameplayTag& tag,
                                              bool                logNotFound ) const {

     for ( const auto& action : _nativeInputActions ) {
         if ( action._inputAction && ( action._inputTag == tag ) ) {
             return action._inputAction;
         }
     }

     if ( logNotFound ) {
         UE_LOG(
             LogMS, Error,
             TEXT( "Can't find NativeInputAction for InputTag [%s] on InputConfig[%s]." ),
             *tag.ToString(), *GetNameSafe( this ) );
     }

     return nullptr;
 }

 const UInputAction*
 UMSInputConfig::FindAbilityInputActionForTag( const FGameplayTag& tag,
                                               bool                logNotFound ) const {

     for ( const auto& a : _abilityInputActions ) {
         if ( a._inputAction && ( a._inputTag == tag ) ) {
             return a._inputAction;
         }
     }

     if ( logNotFound ) {
         UE_LOG(
             LogMS, Error,
             TEXT(
                 "Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."
                 ),
             *tag.ToString(), *GetNameSafe( this ) );
     }
     return nullptr;
 }
