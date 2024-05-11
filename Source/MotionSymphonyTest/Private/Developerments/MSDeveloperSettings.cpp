// Fill out your copyright notice in the Description page of Project Settings.


#include "Developerments/MSDeveloperSettings.h"
#include "Misc/App.h"

UMSDeveloperSettings::UMSDeveloperSettings() {}

FName UMSDeveloperSettings::GetCategoryName() const {
    return FApp::GetProjectName();
}
