// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AController;
class ASpectatorPawn;
#ifdef EXTENDEDCONTROLSTATES_ECStateSubsystem_generated_h
#error "ECStateSubsystem.generated.h already included, missing '#pragma once' in ECStateSubsystem.h"
#endif
#define EXTENDEDCONTROLSTATES_ECStateSubsystem_generated_h

#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_30_DELEGATE \
struct _Script_ExtendedControlStates_eventOnRespawnRequestSignature_Parms \
{ \
	AController* Controller; \
}; \
static inline void FOnRespawnRequestSignature_DelegateWrapper(const FMulticastScriptDelegate& OnRespawnRequestSignature, AController* Controller) \
{ \
	_Script_ExtendedControlStates_eventOnRespawnRequestSignature_Parms Parms; \
	Parms.Controller=Controller; \
	OnRespawnRequestSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_SPARSE_DATA
#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execRespawnInWorld); \
	DECLARE_FUNCTION(execBeginSpectating); \
	DECLARE_FUNCTION(execIsPlaying); \
	DECLARE_FUNCTION(execIsSpectating);


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execRespawnInWorld); \
	DECLARE_FUNCTION(execBeginSpectating); \
	DECLARE_FUNCTION(execIsPlaying); \
	DECLARE_FUNCTION(execIsSpectating);


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUECStateSubsystem(); \
	friend struct Z_Construct_UClass_UECStateSubsystem_Statics; \
public: \
	DECLARE_CLASS(UECStateSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ExtendedControlStates"), NO_API) \
	DECLARE_SERIALIZER(UECStateSubsystem)


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_INCLASS \
private: \
	static void StaticRegisterNativesUECStateSubsystem(); \
	friend struct Z_Construct_UClass_UECStateSubsystem_Statics; \
public: \
	DECLARE_CLASS(UECStateSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ExtendedControlStates"), NO_API) \
	DECLARE_SERIALIZER(UECStateSubsystem)


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UECStateSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UECStateSubsystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UECStateSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UECStateSubsystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UECStateSubsystem(UECStateSubsystem&&); \
	NO_API UECStateSubsystem(const UECStateSubsystem&); \
public:


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UECStateSubsystem() { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UECStateSubsystem(UECStateSubsystem&&); \
	NO_API UECStateSubsystem(const UECStateSubsystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UECStateSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UECStateSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UECStateSubsystem)


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_PRIVATE_PROPERTY_OFFSET
#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_32_PROLOG
#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_SPARSE_DATA \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_RPC_WRAPPERS \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_INCLASS \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_PRIVATE_PROPERTY_OFFSET \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_SPARSE_DATA \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_INCLASS_NO_PURE_DECLS \
	Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h_36_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EXTENDEDCONTROLSTATES_API UClass* StaticClass<class UECStateSubsystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Lightbringer_Plugins_ExtendedControlStates_Source_ExtendedControlStates_Public_ECStateSubsystem_h


#define FOREACH_ENUM_ESPECTATINGSTATE(op) \
	op(ESpectatingState::Spectating) \
	op(ESpectatingState::Playing) \
	op(ESpectatingState::Default) 

enum class ESpectatingState : uint8;
template<> EXTENDEDCONTROLSTATES_API UEnum* StaticEnum<ESpectatingState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
