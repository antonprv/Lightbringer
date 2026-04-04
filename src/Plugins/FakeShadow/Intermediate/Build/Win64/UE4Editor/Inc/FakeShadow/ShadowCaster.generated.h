// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USkeletalMeshComponent;
#ifdef FAKESHADOW_ShadowCaster_generated_h
#error "ShadowCaster.generated.h already included, missing '#pragma once' in ShadowCaster.h"
#endif
#define FAKESHADOW_ShadowCaster_generated_h

#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_SPARSE_DATA
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_RPC_WRAPPERS \
	virtual void GetShadowCasterMesh_Implementation(USkeletalMeshComponent*& OutMesh) {}; \
 \
	DECLARE_FUNCTION(execGetShadowCasterMesh);


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetShadowCasterMesh);


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_EVENT_PARMS \
	struct ShadowCaster_eventGetShadowCasterMesh_Parms \
	{ \
		USkeletalMeshComponent* OutMesh; \
	};


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_CALLBACK_WRAPPERS
#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FAKESHADOW_API UShadowCaster(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UShadowCaster) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FAKESHADOW_API, UShadowCaster); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UShadowCaster); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	FAKESHADOW_API UShadowCaster(UShadowCaster&&); \
	FAKESHADOW_API UShadowCaster(const UShadowCaster&); \
public:


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FAKESHADOW_API UShadowCaster(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	FAKESHADOW_API UShadowCaster(UShadowCaster&&); \
	FAKESHADOW_API UShadowCaster(const UShadowCaster&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FAKESHADOW_API, UShadowCaster); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UShadowCaster); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UShadowCaster)


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUShadowCaster(); \
	friend struct Z_Construct_UClass_UShadowCaster_Statics; \
public: \
	DECLARE_CLASS(UShadowCaster, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/FakeShadow"), FAKESHADOW_API) \
	DECLARE_SERIALIZER(UShadowCaster)


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_GENERATED_UINTERFACE_BODY() \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_GENERATED_UINTERFACE_BODY() \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IShadowCaster() {} \
public: \
	typedef UShadowCaster UClassType; \
	typedef IShadowCaster ThisClass; \
	static void Execute_GetShadowCasterMesh(UObject* O, USkeletalMeshComponent*& OutMesh); \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_INCLASS_IINTERFACE \
protected: \
	virtual ~IShadowCaster() {} \
public: \
	typedef UShadowCaster UClassType; \
	typedef IShadowCaster ThisClass; \
	static void Execute_GetShadowCasterMesh(UObject* O, USkeletalMeshComponent*& OutMesh); \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_15_PROLOG \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_EVENT_PARMS


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_SPARSE_DATA \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_RPC_WRAPPERS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_CALLBACK_WRAPPERS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_SPARSE_DATA \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_CALLBACK_WRAPPERS \
	Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h_18_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FAKESHADOW_API UClass* StaticClass<class UShadowCaster>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Lightbringer_Plugins_FakeShadow_Source_FakeShadow_Public_Interfaces_ShadowCaster_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
