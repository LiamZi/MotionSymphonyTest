// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/MSPawnData.h"

UMSPawnData::UMSPawnData( const FObjectInitializer& object ) : Super{ object } {
    _pawnClass   = nullptr;
    _inputConfig = nullptr;
    _cameraMode  = nullptr;
}
