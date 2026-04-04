// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FakeShadow/Public/Components/FakeShadowComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFakeShadowComponent() {}
// Cross Module References
	FAKESHADOW_API UClass* Z_Construct_UClass_UFakeShadowComponent_NoRegister();
	FAKESHADOW_API UClass* Z_Construct_UClass_UFakeShadowComponent();
	ENGINE_API UClass* Z_Construct_UClass_UDecalComponent();
	UPackage* Z_Construct_UPackage__Script_FakeShadow();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
// End Cross Module References
	void UFakeShadowComponent::StaticRegisterNativesUFakeShadowComponent()
	{
	}
	UClass* Z_Construct_UClass_UFakeShadowComponent_NoRegister()
	{
		return UFakeShadowComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFakeShadowComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ShadowRenderer_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ShadowRenderer;
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraArrow_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraArrow;
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ShadowOwner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ShadowOwner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FakeShadowMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FakeShadowMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FakeShadowTexture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FakeShadowTexture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFakeShadowComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDecalComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FakeShadow,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Collision Object Physics SceneComponent Activation Components|Activation Mobility Trigger PhysicsVolume" },
		{ "IncludePath", "Components/FakeShadowComponent.h" },
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowRenderer_MetaData[] = {
		{ "Category", "FakeShadowComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowRenderer = { "ShadowRenderer", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFakeShadowComponent, ShadowRenderer), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowRenderer_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowRenderer_MetaData)) };
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_CameraArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_CameraArrow = { "CameraArrow", nullptr, (EPropertyFlags)0x0040000800080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFakeShadowComponent, CameraArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_CameraArrow_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_CameraArrow_MetaData)) };
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowOwner_MetaData[] = {
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowOwner = { "ShadowOwner", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFakeShadowComponent, ShadowOwner), Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowOwner_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowOwner_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowMaterial = { "FakeShadowMaterial", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFakeShadowComponent, FakeShadowMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowTexture_MetaData[] = {
		{ "ModuleRelativePath", "Public/Components/FakeShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowTexture = { "FakeShadowTexture", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFakeShadowComponent, FakeShadowTexture), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowTexture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFakeShadowComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowRenderer,
#if WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_CameraArrow,
#endif // WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_ShadowOwner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFakeShadowComponent_Statics::NewProp_FakeShadowTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFakeShadowComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFakeShadowComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFakeShadowComponent_Statics::ClassParams = {
		&UFakeShadowComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFakeShadowComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFakeShadowComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFakeShadowComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFakeShadowComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFakeShadowComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFakeShadowComponent, 1512244663);
	template<> FAKESHADOW_API UClass* StaticClass<UFakeShadowComponent>()
	{
		return UFakeShadowComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFakeShadowComponent(Z_Construct_UClass_UFakeShadowComponent, &UFakeShadowComponent::StaticClass, TEXT("/Script/FakeShadow"), TEXT("UFakeShadowComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFakeShadowComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
