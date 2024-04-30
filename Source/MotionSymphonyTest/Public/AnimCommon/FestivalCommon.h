// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FestivalCommon.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class WeaponType : uint8
{
    WT_NONE UMETA(DisplayName = "None"),
    WT_SWORD UMETA(DisplayName = "Sword"),
    WT_DUALBLADE UMETA(DisplayName = "Dual Blade"),
    WT_AXE_OR_BLUNT UMETA(DisplayName = "Axe or Blunt"),
    WT_SHIELD UMETA(DisplayName = "Shield"),
    WT_BOW UMETA(DisplayName = "Bow"),
    WT_WAND UMETA(DisplayName = "Wand")
};