// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
enum class EVelocityScaleType : uint8;
struct FRotator;
#ifdef MATHUTILS_MathUtilStatics_generated_h
#error "MathUtilStatics.generated.h already included, missing '#pragma once' in MathUtilStatics.h"
#endif
#define MATHUTILS_MathUtilStatics_generated_h

#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_SPARSE_DATA
#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCalculateAcceleration); \
	DECLARE_FUNCTION(execCalculateDirection);


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCalculateAcceleration); \
	DECLARE_FUNCTION(execCalculateDirection);


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMathUtilStatics(); \
	friend struct Z_Construct_UClass_UMathUtilStatics_Statics; \
public: \
	DECLARE_CLASS(UMathUtilStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MathUtils"), NO_API) \
	DECLARE_SERIALIZER(UMathUtilStatics)


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUMathUtilStatics(); \
	friend struct Z_Construct_UClass_UMathUtilStatics_Statics; \
public: \
	DECLARE_CLASS(UMathUtilStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MathUtils"), NO_API) \
	DECLARE_SERIALIZER(UMathUtilStatics)


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMathUtilStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMathUtilStatics) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMathUtilStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMathUtilStatics); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMathUtilStatics(UMathUtilStatics&&); \
	NO_API UMathUtilStatics(const UMathUtilStatics&); \
public:


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMathUtilStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMathUtilStatics(UMathUtilStatics&&); \
	NO_API UMathUtilStatics(const UMathUtilStatics&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMathUtilStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMathUtilStatics); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMathUtilStatics)


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_PRIVATE_PROPERTY_OFFSET
#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_20_PROLOG
#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_SPARSE_DATA \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_RPC_WRAPPERS \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_INCLASS \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_SPARSE_DATA \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_INCLASS_NO_PURE_DECLS \
	Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MATHUTILS_API UClass* StaticClass<class UMathUtilStatics>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Lightbringer_Plugins_MathUtils_Source_MathUtils_Public_MathUtilStatics_h


#define FOREACH_ENUM_EVELOCITYSCALETYPE(op) \
	op(EVelocityScaleType::Meters) \
	op(EVelocityScaleType::Kilometers) 

enum class EVelocityScaleType : uint8;
template<> MATHUTILS_API UEnum* StaticEnum<EVelocityScaleType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
