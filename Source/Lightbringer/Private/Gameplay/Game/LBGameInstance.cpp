// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Game/LBGameInstance.h"

#include "AnimationSharingManager.h"

#include "View/Subsystems/QualitySettingsSubsystem.h"
#include "View/Rendering/GraphicsPresetManager.h"

DEFINE_LOG_CATEGORY_STATIC(LightBringerGameInstanceLog, All, All)

void ULBGameInstance::OnStart()
{
    Super::OnStart();

    // Apply settings if world is created already
    if (UWorld* World = GetWorld())
    {
        if (World->IsGameWorld())
        {
            ApplyGraphicsSettingsAfterWorld(
                World, UWorld::InitializationValues());
        }
    }

    // ...and if not, we subscribe and apply when it is.
    FWorldDelegates::OnPostWorldInitialization.AddUObject(
        this, &ULBGameInstance::ApplyGraphicsSettingsAfterWorld);
}

void ULBGameInstance::ApplyGraphicsSettingsAfterWorld(
    UWorld* World, const UWorld::InitializationValues IVS)

{
    if (!World || !World->IsGameWorld()) return;

    if (UQualitySettingsSubsystem* QualitySettingsSubsystem =
            UQualitySettingsSubsystem::Get(World))
    {
        QualitySettingsSubsystem->GetGraphicsPresetManager()
            ->ApplyDefaultQualitySettings();
    }
    else
    {
        UE_LOG(LightBringerGameInstanceLog, Fatal,  //
            TEXT("GameInstanceFailed to initialize subsystem after world "
                 "creation"))
    }
}

void ULBGameInstance::Shutdown()
{
    FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
    Super::Shutdown();
}