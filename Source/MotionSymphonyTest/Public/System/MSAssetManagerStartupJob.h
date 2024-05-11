// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"

DECLARE_DELEGATE_OneParam( MSAssetManagerStartupJobSubstepProgress, float );

struct FMSAssetManagerStartupJob {
    MSAssetManagerStartupJobSubstepProgress substepProgressDelegate;
    TFunction< void( const FMSAssetManagerStartupJob&, TSharedPtr< FStreamableHandle >& ) >
        _jobFunc;
    FString _jobName;
    float   _jobWeight;
    mutable double _lastUpdate = 0;


    FMSAssetManagerStartupJob(
        const FString&                                               inJobName,
        const TFunction< void( const FMSAssetManagerStartupJob&,
                               TSharedPtr< FStreamableHandle >& ) >& inJobFunc,
        float                                                        inJobWeight );

    TSharedPtr< FStreamableHandle > DoJob() const;

    void UpdateSubstepProgress(float newProgress) const
    {
        substepProgressDelegate.ExecuteIfBound( newProgress );
    }

    void UpdateSubstepProgressFromStreamable(TSharedRef<FStreamableHandle> handle) const
    {
        if (substepProgressDelegate.IsBound())
        {
            double now = FPlatformTime::Seconds();
            if ((_lastUpdate - now) > (1.0 / 60))
            {
                substepProgressDelegate.Execute( handle->GetProgress() );
                _lastUpdate = now;
            }
        }
    }

};
