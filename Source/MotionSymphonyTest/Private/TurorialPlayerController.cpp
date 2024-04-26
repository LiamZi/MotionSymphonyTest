// Fill out your copyright notice in the Description page of Project Settings.


#include "TurorialPlayerController.h"
#include "Components/InputComponent.h"
#include "Misc/Exec.h"
#include "TurorialCharacter.h"
#include "InputDataConfig.h"


ATurorialPlayerController::ATurorialPlayerController()
	: _inputActions{ nullptr }
	, _character{ nullptr }
	, _isBaseSpeedWalk{ false }
{
	_character = Cast<ATurorialCharacter>(GetCharacter());
}

void ATurorialPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	auto input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!_inputActions) return;

	input->BindAction(_inputActions->_move, ETriggerEvent::Triggered, this, &ATurorialPlayerController::Move);
	input->BindAction(_inputActions->_move, ETriggerEvent::Canceled, this, &ATurorialPlayerController::Move);
	input->BindAction(_inputActions->_move, ETriggerEvent::Completed, this, &ATurorialPlayerController::Move);
	input->BindAction(_inputActions->_look, ETriggerEvent::Triggered, this, &ATurorialPlayerController::Look);
	input->BindAction(_inputActions->_jump, ETriggerEvent::Triggered, this, &ATurorialPlayerController::Jump);
	input->BindAction(_inputActions->_walk, ETriggerEvent::Started, this, &ATurorialPlayerController::Walk);
	input->BindAction(_inputActions->_sprint, ETriggerEvent::Started, this, &ATurorialPlayerController::SprintStarted);
	input->BindAction(_inputActions->_sprint, ETriggerEvent::Canceled, this, &ATurorialPlayerController::SprintEnded);
	input->BindAction(_inputActions->_sprint, ETriggerEvent::Completed, this, &ATurorialPlayerController::SprintEnded);

	input->BindAction(_inputActions->_strafe, ETriggerEvent::Started, this, &ATurorialPlayerController::StrafeStarted);
	input->BindAction(_inputActions->_strafe, ETriggerEvent::Canceled, this, &ATurorialPlayerController::StrafeEnded);
	input->BindAction(_inputActions->_strafe, ETriggerEvent::Completed, this, &ATurorialPlayerController::StrafeEnded);
}

void ATurorialPlayerController::OnPossess(APawn* aPawn)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Warning: Exec the OnPossess."));

	Super::OnPossess(aPawn);

	//_character = Cast<ATurorialCharacter>(GetPawn());

	//if (IsValid(_character))
	//{
	//	
	//}
	//else
	//{

	//}
}


void ATurorialPlayerController::Move(const FInputActionValue& value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Warning: Exec the Move."));

	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	const FVector2D moveValue = value.Get<FVector2D>();
	if (_character) _character->Move(moveValue);
}

void ATurorialPlayerController::Look(const FInputActionValue& value)
{

	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (_character)
	{
		const FVector2D v = value.Get<FVector2D>();

		_character->AddControllerYawInput(v.X);
		_character->AddControllerPitchInput(v.Y);
	}
}

void ATurorialPlayerController::Jump()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Warning: Exec the Jump."));

	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (_character) _character->Jump();

}

void ATurorialPlayerController::Walk()
{
	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (!_character) return;

	auto speedTag = _character->GetSpeedTag();
	auto walkTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Motion.Speed.Walk"));
	if (speedTag == walkTag)
	{
		_character->BeginRun();
		_isBaseSpeedWalk = false;
	}
	else
	{
		_character->BeginWalk();
		_isBaseSpeedWalk = true;
	}
}

void ATurorialPlayerController::SprintStarted()
{
	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (!_character) return;

	_character->BeginSprint();
}

void ATurorialPlayerController::SprintEnded()
{
	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (!_character) return;

	if (_isBaseSpeedWalk)
	{
		_character->BeginWalk();
	}
	else
	{
		_character->BeginRun();
	}
}

void ATurorialPlayerController::StrafeStarted()
{
	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (!_character) return;

	_character->BeginStrafe();
}

void ATurorialPlayerController::StrafeEnded()
{
	if (!_character)
	{
		_character = Cast<ATurorialCharacter>(GetCharacter());
	}

	if (!_character) return;

	_character->BeginNeutral();
}
