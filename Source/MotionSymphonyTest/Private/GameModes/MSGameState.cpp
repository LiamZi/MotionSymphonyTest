// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MSGameState.h"
#include "GameModes/MSExperienceManagerComponent.h"

AMSGameState::AMSGameState( const FObjectInitializer& object ) 
	: Super{ object } 
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;


    _experienceManagerComponent = CreateDefaultSubobject< UMSExperienceManagerComponent >(
        TEXT( "ExperienceManagerComponent" ) );
}

void AMSGameState::PreInitializeComponents() 
{
    Super::PreInitializeComponents();
}

void AMSGameState::PostInitializeComponents() 
{
    Super::PostInitializeComponents();
}

void AMSGameState::EndPlay( const EEndPlayReason::Type reason ) 
{
    Super::EndPlay( reason );
}

void AMSGameState::Tick( float deltaSeconds ) 
{
    Super::Tick( deltaSeconds );

}

void AMSGameState::AddPlayerState( APlayerState* state ) 
{
    Super::AddPlayerState( state );
}

void AMSGameState::RemovePlayerState( APlayerState* state ) 
{
    Super::RemovePlayerState( state );
}

void AMSGameState::SeamlessTravelTransitionCheckpoint( bool isTransitionMap ) 
{

}
