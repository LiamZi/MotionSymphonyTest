// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MotionSymphonyTest : ModuleRules
{
    public MotionSymphonyTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                "MotionSymphonyTest"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject",
                "ApplicationCore",
                "Engine", 
                "MotionSymphony", 
                "GameplayTags",
                "GameplayTasks",
                "PhysicsCore",
                "AIModule",
                "GameplayAbilities",
                "GameFeatures",
                "DataRegistry",
                "ModularGameplay",
                "MSModularActors",
                "PropertyPath",

            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "EnhancedInput",
                "RenderCore",
                "RHI",
                "CommonUI",
                "CommonInput",
                "AudioMixer",
                "EngineSettings",
                "Projects",

            }
        );

        ////PublicIncludePathModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });


        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
