// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FAKESHADOW_FakeShadowComponent_generated_h
#error "FakeShadowComponent.generated.h already included, missing '#pragma once' in FakeShadowComponent.h"
#endif
#define FAKESHADOW_FakeShadowComponent_generated_h

#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_SPARSE_DATA
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_RPC_WRAPPERS
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFakeShadowComponent(); \
	friend struct Z_Construct_UClass_UFakeShadowComponent_Statics; \
public: \
	DECLARE_CLASS(UFakeShadowComponent, UDecalComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FakeShadow"), NO_API) \
	DECLARE_SERIALIZER(UFakeShadowComponent)


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUFakeShadowComponent(); \
	friend struct Z_Construct_UClass_UFakeShadowComponent_Statics; \
public: \
	DECLARE_CLASS(UFakeShadowComponent, UDecalComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FakeShadow"), NO_API) \
	DECLARE_SERIALIZER(UFakeShadowComponent)


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFakeShadowComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFakeShadowComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFakeShadowComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFakeShadowComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFakeShadowComponent(UFakeShadowComponent&&); \
	NO_API UFakeShadowComponent(const UFakeShadowComponent&); \
public:


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFakeShadowComponent(UFakeShadowComponent&&); \
	NO_API UFakeShadowComponent(const UFakeShadowComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFakeShadowComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFakeShadowComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFakeShadowComponent)


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ShadowOwner() { return STRUCT_OFFSET(UFakeShadowComponent, ShadowOwner); } \
	FORCEINLINE static uint32 __PPO__FakeShadowMaterial() { return STRUCT_OFFSET(UFakeShadowComponent, FakeShadowMaterial); } \
	FORCEINLINE static uint32 __PPO__FakeShadowTexture() { return STRUCT_OFFSET(UFakeShadowComponent, FakeShadowTexture); }


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_23_PROLOG
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_SPARSE_DATA \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_RPC_WRAPPERS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_INCLASS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_SPARSE_DATA \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_INCLASS_NO_PURE_DECLS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FAKESHADOW_API UClass* StaticClass<class UFakeShadowComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Components_FakeShadowComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
