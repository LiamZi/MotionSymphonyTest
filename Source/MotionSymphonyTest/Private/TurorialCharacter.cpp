// Fill out your copyright notice in the Description page of Project Settings.


#include "TurorialCharacter.h"
#include "TurorialPlayerController.h"
#include "Components/TrajectoryGenerator.h"
#include "Components/TrajectoryErrorWarping.h"
#include "Components/DistanceMatching.h"
#include "Enumerations/EMotionMatchingEnums.h"
#include "BlueprintGameplayTagLibrary.h"



// Sets default values
ATurorialCharacter::ATurorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//_trajectoryGenerator
	_trajectoryGenerator = CreateDefaultSubobject<UTrajectoryGenerator>(TEXT("TestTrajectoryGenerator"));
	_trajectoryErrorWarping = CreateDefaultSubobject<UTrajectoryErrorWarping>(TEXT("TestTrajectoryErrorWarping"));
	_distanceMatching = CreateDefaultSubobject<UDistanceMatching>(TEXT("TestDistanceMatching"));

}

// Called when the game starts or when spawned
void ATurorialCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurorialCharacter::BeginNeutral()
{
	SetStyleTag(UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Motion.Sytle.Neutral")));
	_trajectoryGenerator->TrajectoryBehaviour = ETrajectoryMoveMode::Standard;
	_trajectoryErrorWarping->SetMode(ETrajectoryErrorWarpMode::Standard, 60.0f, 50.0f, 0.25f, 30.0f);
}

void ATurorialCharacter::SetStyleTag(FGameplayTag tag)
{
	UBlueprintGameplayTagLibrary::RemoveGameplayTag(_locomotionTags, _styleTag);
	_styleTag = tag;
	UBlueprintGameplayTagLibrary::AddGameplayTag(_locomotionTags, _styleTag);
}

// Called every frame
void ATurorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto pc = Cast<APlayerController>(GetController());
	if (pc != nullptr && pc->IsLocalPlayerController())
	{
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		subSystem->ClearAllMappings();
		subSystem->AddMappingContext(_inputMapping, 0);
	}


}
