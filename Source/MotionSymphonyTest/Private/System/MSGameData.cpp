// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MSGameData.h"
#include "System/MSAssetManager.h"

UMSGameData::UMSGameData() {}

const UMSGameData& UMSGameData::Get() {
    return UMSAssetManager::Get().GetGameData();
}
