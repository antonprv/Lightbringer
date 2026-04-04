// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FakeShadow/Public/Components/BlobShadowComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBlobShadowComponent() {}
// Cross Module References
	FAKESHADOW_API UClass* Z_Construct_UClass_UBlobShadowComponent_NoRegister();
	FAKESHADOW_API UClass* Z_Construct_UClass_UBlobShadowComponent();
	ENGINE_API UClass* Z_Construct_UClass_UDecalComponent();
	UPackage* Z_Construct_UPackage__Script_FakeShadow();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
// End Cross Module References
	void UBlobShadowComponent::StaticRegisterNativesUBlobShadowComponent()
	{
	}
	UClass* Z_Construct_UClass_UBlobShadowComponent_NoRegister()
	{
		return UBlobShadowComponent::StaticClass();
	}
	struct Z_Construct_UClass_UBlobShadowComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsDecalShadowDebugEnabled_MetaData[];
#endif
		static void NewProp_bIsDecalShadowDebugEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsDecalShadowDebugEnabled;
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DecalTraceDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DecalTraceDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterOwner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterOwner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BlobShadowMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BlobShadowMaterial;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBlobShadowComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDecalComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FakeShadow,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlobShadowComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Collision Object Physics SceneComponent Activation Components|Activation Mobility Trigger PhysicsVolume" },
		{ "IncludePath", "Components/BlobShadowComponent.h" },
		{ "ModuleRelativePath", "Public/Components/BlobShadowComponent.h" },
	};
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled_MetaData[] = {
		{ "Category", "BlobShadowComponent" },
		{ "ModuleRelativePath", "Public/Components/BlobShadowComponent.h" },
	};
#endif
	void Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled_SetBit(void* Obj)
	{
		((UBlobShadowComponent*)Obj)->bIsDecalShadowDebugEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled = { "bIsDecalShadowDebugEnabled", nullptr, (EPropertyFlags)0x0010000800000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UBlobShadowComponent), &Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled_SetBit, METADATA_PARAMS(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled_MetaData)) };
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_DecalTraceDistance_MetaData[] = {
		{ "Category", "BlobShadowComponent" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/Components/BlobShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_DecalTraceDistance = { "DecalTraceDistance", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBlobShadowComponent, DecalTraceDistance), METADATA_PARAMS(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_DecalTraceDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_DecalTraceDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_CharacterOwner_MetaData[] = {
		{ "ModuleRelativePath", "Public/Components/BlobShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_CharacterOwner = { "CharacterOwner", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBlobShadowComponent, CharacterOwner), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_CharacterOwner_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_CharacterOwner_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_BlobShadowMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/Components/BlobShadowComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_BlobShadowMaterial = { "BlobShadowMaterial", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBlobShadowComponent, BlobShadowMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_BlobShadowMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_BlobShadowMaterial_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBlobShadowComponent_Statics::PropPointers[] = {
#if WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_bIsDecalShadowDebugEnabled,
#endif // WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_DecalTraceDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_CharacterOwner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlobShadowComponent_Statics::NewProp_BlobShadowMaterial,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBlobShadowComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBlobShadowComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBlobShadowComponent_Statics::ClassParams = {
		&UBlobShadowComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBlobShadowComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UBlobShadowComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBlobShadowComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBlobShadowComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBlobShadowComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBlobShadowComponent, 3834636685);
	template<> FAKESHADOW_API UClass* StaticClass<UBlobShadowComponent>()
	{
		return UBlobShadowComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBlobShadowComponent(Z_Construct_UClass_UBlobShadowComponent, &UBlobShadowComponent::StaticClass, TEXT("/Script/FakeShadow"), TEXT("UBlobShadowComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBlobShadowComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
