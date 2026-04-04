// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MathUtils/Public/MathUtilStatics.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMathUtilStatics() {}
// Cross Module References
	MATHUTILS_API UEnum* Z_Construct_UEnum_MathUtils_EVelocityScaleType();
	UPackage* Z_Construct_UPackage__Script_MathUtils();
	MATHUTILS_API UClass* Z_Construct_UClass_UMathUtilStatics_NoRegister();
	MATHUTILS_API UClass* Z_Construct_UClass_UMathUtilStatics();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
// End Cross Module References
	static UEnum* EVelocityScaleType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_MathUtils_EVelocityScaleType, Z_Construct_UPackage__Script_MathUtils(), TEXT("EVelocityScaleType"));
		}
		return Singleton;
	}
	template<> MATHUTILS_API UEnum* StaticEnum<EVelocityScaleType>()
	{
		return EVelocityScaleType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EVelocityScaleType(EVelocityScaleType_StaticEnum, TEXT("/Script/MathUtils"), TEXT("EVelocityScaleType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_MathUtils_EVelocityScaleType_Hash() { return 3375522178U; }
	UEnum* Z_Construct_UEnum_MathUtils_EVelocityScaleType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_MathUtils();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EVelocityScaleType"), 0, Get_Z_Construct_UEnum_MathUtils_EVelocityScaleType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EVelocityScaleType::Meters", (int64)EVelocityScaleType::Meters },
				{ "EVelocityScaleType::Kilometers", (int64)EVelocityScaleType::Kilometers },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "/**\n *\n */" },
				{ "Kilometers.Comment", "/**\n *\n */" },
				{ "Kilometers.Name", "EVelocityScaleType::Kilometers" },
				{ "Meters.Comment", "/**\n *\n */" },
				{ "Meters.Name", "EVelocityScaleType::Meters" },
				{ "ModuleRelativePath", "Public/MathUtilStatics.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_MathUtils,
				nullptr,
				"EVelocityScaleType",
				"EVelocityScaleType",
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
	DEFINE_FUNCTION(UMathUtilStatics::execCalculateAcceleration)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Velocity);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
		P_GET_ENUM(EVelocityScaleType,Z_Param_VelocityScale);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UMathUtilStatics::CalculateAcceleration(Z_Param_Out_Velocity,Z_Param_DeltaTime,EVelocityScaleType(Z_Param_VelocityScale));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMathUtilStatics::execCalculateDirection)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Velocity);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_BaseRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UMathUtilStatics::CalculateDirection(Z_Param_Out_Velocity,Z_Param_Out_BaseRotation);
		P_NATIVE_END;
	}
	void UMathUtilStatics::StaticRegisterNativesUMathUtilStatics()
	{
		UClass* Class = UMathUtilStatics::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CalculateAcceleration", &UMathUtilStatics::execCalculateAcceleration },
			{ "CalculateDirection", &UMathUtilStatics::execCalculateDirection },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics
	{
		struct MathUtilStatics_eventCalculateAcceleration_Parms
		{
			FVector Velocity;
			float DeltaTime;
			EVelocityScaleType VelocityScale;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Velocity;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_VelocityScale_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_VelocityScale;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_Velocity_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateAcceleration_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_Velocity_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_Velocity_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateAcceleration_Parms, DeltaTime), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_VelocityScale_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_VelocityScale = { "VelocityScale", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateAcceleration_Parms, VelocityScale), Z_Construct_UEnum_MathUtils_EVelocityScaleType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateAcceleration_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_Velocity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_DeltaTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_VelocityScale_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_VelocityScale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::Function_MetaDataParams[] = {
		{ "Category", "Math" },
		{ "ModuleRelativePath", "Public/MathUtilStatics.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMathUtilStatics, nullptr, "CalculateAcceleration", nullptr, nullptr, sizeof(MathUtilStatics_eventCalculateAcceleration_Parms), Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics
	{
		struct MathUtilStatics_eventCalculateDirection_Parms
		{
			FVector Velocity;
			FRotator BaseRotation;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Velocity;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseRotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_BaseRotation;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_Velocity_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateDirection_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_Velocity_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_Velocity_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_BaseRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_BaseRotation = { "BaseRotation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateDirection_Parms, BaseRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_BaseRotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_BaseRotation_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MathUtilStatics_eventCalculateDirection_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_Velocity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_BaseRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::Function_MetaDataParams[] = {
		{ "Category", "Math" },
		{ "ModuleRelativePath", "Public/MathUtilStatics.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMathUtilStatics, nullptr, "CalculateDirection", nullptr, nullptr, sizeof(MathUtilStatics_eventCalculateDirection_Parms), Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMathUtilStatics_CalculateDirection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMathUtilStatics_CalculateDirection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UMathUtilStatics_NoRegister()
	{
		return UMathUtilStatics::StaticClass();
	}
	struct Z_Construct_UClass_UMathUtilStatics_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMathUtilStatics_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_MathUtils,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UMathUtilStatics_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMathUtilStatics_CalculateAcceleration, "CalculateAcceleration" }, // 1825168654
		{ &Z_Construct_UFunction_UMathUtilStatics_CalculateDirection, "CalculateDirection" }, // 2421864710
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMathUtilStatics_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MathUtilStatics.h" },
		{ "ModuleRelativePath", "Public/MathUtilStatics.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMathUtilStatics_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMathUtilStatics>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMathUtilStatics_Statics::ClassParams = {
		&UMathUtilStatics::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UMathUtilStatics_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMathUtilStatics_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMathUtilStatics()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMathUtilStatics_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMathUtilStatics, 2834212891);
	template<> MATHUTILS_API UClass* StaticClass<UMathUtilStatics>()
	{
		return UMathUtilStatics::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMathUtilStatics(Z_Construct_UClass_UMathUtilStatics, &UMathUtilStatics::StaticClass, TEXT("/Script/MathUtils"), TEXT("UMathUtilStatics"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMathUtilStatics);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
