// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FakeShadow/Public/Interfaces/ShadowCaster.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeShadowCaster() {}
// Cross Module References
	FAKESHADOW_API UClass* Z_Construct_UClass_UShadowCaster_NoRegister();
	FAKESHADOW_API UClass* Z_Construct_UClass_UShadowCaster();
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	UPackage* Z_Construct_UPackage__Script_FakeShadow();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(IShadowCaster::execGetShadowCasterMesh)
	{
		P_GET_OBJECT_REF(USkeletalMeshComponent,Z_Param_Out_OutMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetShadowCasterMesh_Implementation(Z_Param_Out_OutMesh);
		P_NATIVE_END;
	}
	void IShadowCaster::GetShadowCasterMesh(USkeletalMeshComponent*& OutMesh)
	{
		check(0 && "Do not directly call Event functions in Interfaces. Call Execute_GetShadowCasterMesh instead.");
	}
	void UShadowCaster::StaticRegisterNativesUShadowCaster()
	{
		UClass* Class = UShadowCaster::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetShadowCasterMesh", &IShadowCaster::execGetShadowCasterMesh },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OutMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::NewProp_OutMesh_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::NewProp_OutMesh = { "OutMesh", nullptr, (EPropertyFlags)0x0010000000080180, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ShadowCaster_eventGetShadowCasterMesh_Parms, OutMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::NewProp_OutMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::NewProp_OutMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::NewProp_OutMesh,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "Process Input" },
		{ "ModuleRelativePath", "Public/Interfaces/ShadowCaster.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UShadowCaster, nullptr, "GetShadowCasterMesh", nullptr, nullptr, sizeof(ShadowCaster_eventGetShadowCasterMesh_Parms), Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C420C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UShadowCaster_NoRegister()
	{
		return UShadowCaster::StaticClass();
	}
	struct Z_Construct_UClass_UShadowCaster_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UShadowCaster_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_FakeShadow,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UShadowCaster_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UShadowCaster_GetShadowCasterMesh, "GetShadowCasterMesh" }, // 763725245
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UShadowCaster_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Interfaces/ShadowCaster.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UShadowCaster_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IShadowCaster>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UShadowCaster_Statics::ClassParams = {
		&UShadowCaster::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000840A1u,
		METADATA_PARAMS(Z_Construct_UClass_UShadowCaster_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UShadowCaster_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UShadowCaster()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UShadowCaster_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UShadowCaster, 3341121383);
	template<> FAKESHADOW_API UClass* StaticClass<UShadowCaster>()
	{
		return UShadowCaster::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UShadowCaster(Z_Construct_UClass_UShadowCaster, &UShadowCaster::StaticClass, TEXT("/Script/FakeShadow"), TEXT("UShadowCaster"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UShadowCaster);
	static FName NAME_UShadowCaster_GetShadowCasterMesh = FName(TEXT("GetShadowCasterMesh"));
	void IShadowCaster::Execute_GetShadowCasterMesh(UObject* O, USkeletalMeshComponent*& OutMesh)
	{
		check(O != NULL);
		check(O->GetClass()->ImplementsInterface(UShadowCaster::StaticClass()));
		ShadowCaster_eventGetShadowCasterMesh_Parms Parms;
		UFunction* const Func = O->FindFunction(NAME_UShadowCaster_GetShadowCasterMesh);
		if (Func)
		{
			Parms.OutMesh=OutMesh;
			O->ProcessEvent(Func, &Parms);
			OutMesh=Parms.OutMesh;
		}
		else if (auto I = (IShadowCaster*)(O->GetNativeInterfaceAddress(UShadowCaster::StaticClass())))
		{
			I->GetShadowCasterMesh_Implementation(OutMesh);
		}
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
