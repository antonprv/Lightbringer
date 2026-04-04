// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ExtendedControlStates/Public/ECStateSubsystem.h"
#include "Engine/Classes/Engine/GameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeECStateSubsystem() {}
// Cross Module References
	EXTENDEDCONTROLSTATES_API UFunction* Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_ExtendedControlStates();
	ENGINE_API UClass* Z_Construct_UClass_AController_NoRegister();
	EXTENDEDCONTROLSTATES_API UEnum* Z_Construct_UEnum_ExtendedControlStates_ESpectatingState();
	EXTENDEDCONTROLSTATES_API UClass* Z_Construct_UClass_UECStateSubsystem_NoRegister();
	EXTENDEDCONTROLSTATES_API UClass* Z_Construct_UClass_UECStateSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_ASpectatorPawn_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics
	{
		struct _Script_ExtendedControlStates_eventOnRespawnRequestSignature_Parms
		{
			AController* Controller;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Controller;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_ExtendedControlStates_eventOnRespawnRequestSignature_Parms, Controller), Z_Construct_UClass_AController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::NewProp_Controller,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExtendedControlStates, nullptr, "OnRespawnRequestSignature__DelegateSignature", nullptr, nullptr, sizeof(_Script_ExtendedControlStates_eventOnRespawnRequestSignature_Parms), Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_ExtendedControlStates_OnRespawnRequestSignature__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* ESpectatingState_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_ExtendedControlStates_ESpectatingState, Z_Construct_UPackage__Script_ExtendedControlStates(), TEXT("ESpectatingState"));
		}
		return Singleton;
	}
	template<> EXTENDEDCONTROLSTATES_API UEnum* StaticEnum<ESpectatingState>()
	{
		return ESpectatingState_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESpectatingState(ESpectatingState_StaticEnum, TEXT("/Script/ExtendedControlStates"), TEXT("ESpectatingState"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_ExtendedControlStates_ESpectatingState_Hash() { return 1596885596U; }
	UEnum* Z_Construct_UEnum_ExtendedControlStates_ESpectatingState()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_ExtendedControlStates();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESpectatingState"), 0, Get_Z_Construct_UEnum_ExtendedControlStates_ESpectatingState_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESpectatingState::Spectating", (int64)ESpectatingState::Spectating },
				{ "ESpectatingState::Playing", (int64)ESpectatingState::Playing },
				{ "ESpectatingState::Default", (int64)ESpectatingState::Default },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/**\n * This subsystem switches Controller states between possessing spectator and\n * possessing DefaultPawn (Spawning it from the PlayerStart)\n */" },
				{ "Default.Name", "ESpectatingState::Default" },
				{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
				{ "Playing.Name", "ESpectatingState::Playing" },
				{ "Spectating.Name", "ESpectatingState::Spectating" },
				{ "ToolTip", "This subsystem switches Controller states between possessing spectator and\npossessing DefaultPawn (Spawning it from the PlayerStart)" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_ExtendedControlStates,
				nullptr,
				"ESpectatingState",
				"ESpectatingState",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	DEFINE_FUNCTION(UECStateSubsystem::execRespawnInWorld)
	{
		P_GET_OBJECT(AController,Z_Param_Controller);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RespawnInWorld(Z_Param_Controller);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UECStateSubsystem::execBeginSpectating)
	{
		P_GET_OBJECT(AController,Z_Param_Controller);
		P_GET_OBJECT(UClass,Z_Param_SpectatorPawnClass);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->BeginSpectating(Z_Param_Controller,Z_Param_SpectatorPawnClass);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UECStateSubsystem::execIsPlaying)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsPlaying();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UECStateSubsystem::execIsSpectating)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsSpectating();
		P_NATIVE_END;
	}
	void UECStateSubsystem::StaticRegisterNativesUECStateSubsystem()
	{
		UClass* Class = UECStateSubsystem::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BeginSpectating", &UECStateSubsystem::execBeginSpectating },
			{ "IsPlaying", &UECStateSubsystem::execIsPlaying },
			{ "IsSpectating", &UECStateSubsystem::execIsSpectating },
			{ "RespawnInWorld", &UECStateSubsystem::execRespawnInWorld },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics
	{
		struct ECStateSubsystem_eventBeginSpectating_Parms
		{
			AController* Controller;
			TSubclassOf<ASpectatorPawn>  SpectatorPawnClass;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Controller;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_SpectatorPawnClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ECStateSubsystem_eventBeginSpectating_Parms, Controller), Z_Construct_UClass_AController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::NewProp_SpectatorPawnClass = { "SpectatorPawnClass", nullptr, (EPropertyFlags)0x0014000000000080, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ECStateSubsystem_eventBeginSpectating_Parms, SpectatorPawnClass), Z_Construct_UClass_ASpectatorPawn_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::NewProp_Controller,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::NewProp_SpectatorPawnClass,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::Function_MetaDataParams[] = {
		{ "Category", "Extended Controller States" },
		{ "Comment", "// Control state functions\n" },
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
		{ "ToolTip", "Control state functions" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UECStateSubsystem, nullptr, "BeginSpectating", nullptr, nullptr, sizeof(ECStateSubsystem_eventBeginSpectating_Parms), Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UECStateSubsystem_BeginSpectating()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UECStateSubsystem_BeginSpectating_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics
	{
		struct ECStateSubsystem_eventIsPlaying_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((ECStateSubsystem_eventIsPlaying_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ECStateSubsystem_eventIsPlaying_Parms), &Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::Function_MetaDataParams[] = {
		{ "Category", "Extended Controller States" },
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UECStateSubsystem, nullptr, "IsPlaying", nullptr, nullptr, sizeof(ECStateSubsystem_eventIsPlaying_Parms), Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UECStateSubsystem_IsPlaying()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UECStateSubsystem_IsPlaying_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics
	{
		struct ECStateSubsystem_eventIsSpectating_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((ECStateSubsystem_eventIsSpectating_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ECStateSubsystem_eventIsSpectating_Parms), &Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::Function_MetaDataParams[] = {
		{ "Category", "Extended Controller States" },
		{ "Comment", "// Control state fields\n" },
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
		{ "ToolTip", "Control state fields" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UECStateSubsystem, nullptr, "IsSpectating", nullptr, nullptr, sizeof(ECStateSubsystem_eventIsSpectating_Parms), Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UECStateSubsystem_IsSpectating()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UECStateSubsystem_IsSpectating_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics
	{
		struct ECStateSubsystem_eventRespawnInWorld_Parms
		{
			AController* Controller;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Controller;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ECStateSubsystem_eventRespawnInWorld_Parms, Controller), Z_Construct_UClass_AController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::NewProp_Controller,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::Function_MetaDataParams[] = {
		{ "Category", "Extended Controller States" },
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UECStateSubsystem, nullptr, "RespawnInWorld", nullptr, nullptr, sizeof(ECStateSubsystem_eventRespawnInWorld_Parms), Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UECStateSubsystem_NoRegister()
	{
		return UECStateSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_UECStateSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UECStateSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_ExtendedControlStates,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UECStateSubsystem_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UECStateSubsystem_BeginSpectating, "BeginSpectating" }, // 1707151990
		{ &Z_Construct_UFunction_UECStateSubsystem_IsPlaying, "IsPlaying" }, // 3176541052
		{ &Z_Construct_UFunction_UECStateSubsystem_IsSpectating, "IsSpectating" }, // 3584953307
		{ &Z_Construct_UFunction_UECStateSubsystem_RespawnInWorld, "RespawnInWorld" }, // 2709862564
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UECStateSubsystem_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ECStateSubsystem.h" },
		{ "ModuleRelativePath", "Public/ECStateSubsystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UECStateSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UECStateSubsystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UECStateSubsystem_Statics::ClassParams = {
		&UECStateSubsystem::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UECStateSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UECStateSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UECStateSubsystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UECStateSubsystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UECStateSubsystem, 1079279425);
	template<> EXTENDEDCONTROLSTATES_API UClass* StaticClass<UECStateSubsystem>()
	{
		return UECStateSubsystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UECStateSubsystem(Z_Construct_UClass_UECStateSubsystem, &UECStateSubsystem::StaticClass, TEXT("/Script/ExtendedControlStates"), TEXT("UECStateSubsystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UECStateSubsystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
