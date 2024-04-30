// Fill out your copyright notice in the Description page of Project Settings.

#include "TurorialGameMode.h"
#include "TurorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATurorialGameMode::ATurorialGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
        TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
