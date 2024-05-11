// Fill out your copyright notice in the Description page of Project Settings.

#include "System/MSAssetManagerStartupJob.h"

#include "MSLogChannels.h"

FMSAssetManagerStartupJob::FMSAssetManagerStartupJob(
    const FString&                                               inJobName,
    const TFunction< void( const FMSAssetManagerStartupJob&,
                           TSharedPtr< FStreamableHandle >& ) >& inJobFunc,
    float                                                        inJobWeight )
    : _jobFunc{ inJobFunc }, _jobName{ inJobName }, _jobWeight{ inJobWeight } {}

TSharedPtr< FStreamableHandle > FMSAssetManagerStartupJob::DoJob() const {
    const double startTime = FPlatformTime::Seconds();

    TSharedPtr< FStreamableHandle > handle;
    UE_LOG( LogMS, Display, TEXT( "Startup Job \"%s\" starting" ), *_jobName );
    _jobFunc( *this, handle );

    if ( handle.IsValid() ) {
        handle->BindUpdateDelegate( FStreamableUpdateDelegate::CreateRaw(
            this, &FMSAssetManagerStartupJob::UpdateSubstepProgressFromStreamable ) );
        handle->WaitUntilComplete( 0.0f, false );
        handle->BindUpdateDelegate( FStreamableUpdateDelegate() );
    }

    UE_LOG( LogMS, Display, TEXT( "Startup job \"%s\" took %.2f seconds to complete" ),
            *_jobName, FPlatformTime::Seconds() - startTime );

    return handle;
}
