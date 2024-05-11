// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MSWorldSettings.h"

AMSWorldSettings::AMSWorldSettings( const FObjectInitializer& object ) {}


#if WITH_EDITOR
void            AMSWorldSettings::CheckForErrors() {}
FPrimaryAssetId AMSWorldSettings::GetDefaultGameplayExperience() const {
    return FPrimaryAssetId();
}
#endif
