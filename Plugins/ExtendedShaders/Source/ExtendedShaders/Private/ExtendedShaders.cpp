// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ExtendedShaders.h"

#define LOCTEXT_NAMESPACE "FExtendedShadersModule"

#include "Interfaces/IPluginManager.h"
#include "ShaderCore.h"
#include "Misc/Paths.h"

void FExtendedShadersModule::StartupModule()
{
    const FString PluginDir =
        FPaths::Combine(IPluginManager::Get()
                            .FindPlugin(TEXT("ExtendedShaders"))
                            ->GetBaseDir(),
            TEXT("Source/ExtendedShaders/Private/HLSL"));
    AddShaderSourceDirectoryMapping(TEXT("/ExtendedShaders"), PluginDir);
}

void FExtendedShadersModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module. For
    // modules that support dynamic reloading, we call this function before
    // unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FExtendedShadersModule, ExtendedShaders)