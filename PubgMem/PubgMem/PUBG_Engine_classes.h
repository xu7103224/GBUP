#pragma once
#include "PUBG_Basic.h"
#include "PUBG_Engine_structs.h"
#include "vector2D.h"
#include "vector3D.h"
#include "Rotator.h"
#include <d3d9.h>
#include <D3dx9math.h>
class UGameInstance;
class UConsole;
class ULevel;
class USceneComponent;
struct FMinimalViewInfo;




template<class T>
struct TArray
{
	T* Data;
	int32_t Count;
	int32_t Max;
};

// ScriptStruct CoreUObject.Guid
// 0x0010
struct FGuid
{
	int                                                A;                                                        // 0x0000(0x0004) 
	int                                                B;                                                        // 0x0004(0x0004) 
	int                                                C;                                                        // 0x0008(0x0004) 
	int                                                D;                                                        // 0x000C(0x0004) 
};

// ScriptStruct CoreUObject.IntVector
// 0x000C
struct FIntVector
{
	int                                                X;                                                        // 0x0000(0x0004) 
	int                                                Y;                                                        // 0x0004(0x0004) 
	int                                                Z;                                                        // 0x0008(0x0004) 
};

// ScriptStruct Engine.ActorTickFunction
// 0x0008 (0x0058 - 0x0050)
struct FActorTickFunction
{
	unsigned char                                      UnknownData00[0x58];                                       // 0x0050(0x0008) MISSED OFFSET
};

struct FScriptMulticastDelegate
{
	char UnknownData[16];
};

struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{ }

};

// ScriptStruct CoreUObject.Vector4
// 0x0010
struct alignas(16) FVector4
{
	float                                              X;                                                        // 0x0000(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Y;                                                        // 0x0004(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Z;                                                        // 0x0008(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              W;                                                        // 0x000C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct D3DXLine{
	D3DXVECTOR2 t1;
	D3DXVECTOR2 t2;
};


struct FTransform
{
	FQuat									Rotation;                                                 // 0x0000(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	Vector3D								Translation;                                              // 0x0010(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	unsigned char							UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	Vector3D								Scale3D;                                                  // 0x0020(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	unsigned char							UnknownData01[0x4];                                       // 0x002C(0x0004) MISSED OFFSET

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = Translation.x;
		m._42 = Translation.y;
		m._43 = Translation.z;

		float x2 = Rotation.x + Rotation.x;
		float y2 = Rotation.y + Rotation.y;
		float z2 = Rotation.z + Rotation.z;

		float xx2 = Rotation.x * x2;
		float yy2 = Rotation.y * y2;
		float zz2 = Rotation.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * Scale3D.x;
		m._22 = (1.0f - (xx2 + zz2)) * Scale3D.y;
		m._33 = (1.0f - (xx2 + yy2)) * Scale3D.z;

		float yz2 = Rotation.y * z2;
		float wx2 = Rotation.w * x2;
		m._32 = (yz2 - wx2) * Scale3D.z;
		m._23 = (yz2 + wx2) * Scale3D.y;

		float xy2 = Rotation.x * y2;
		float wz2 = Rotation.w * z2;
		m._21 = (xy2 - wz2) * Scale3D.y;
		m._12 = (xy2 + wz2) * Scale3D.x;

		float xz2 = Rotation.x * z2;
		float wy2 = Rotation.w * y2;
		m._31 = (xz2 + wy2) * Scale3D.z;
		m._13 = (xz2 - wy2) * Scale3D.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};


// Class Engine.World
// 0x0978 (0x09A0 - 0x0028)
class UWorld
{
public:
	unsigned char                                         UnknownData00[0x2F];                                      // 0x0000(0x0030) MISSED OFFSET
	class ULevel*                                         PersistentLevel;                                          // 0x0030(0x0008)
	class UNetDriver*                                     NetDriver;                                                // 0x0038(0x0008)
	class ULineBatchComponent*                            LineBatcher;                                              // 0x0040(0x0008)
	class ULineBatchComponent*                            PersistentLineBatcher;                                    // 0x0048(0x0008)
	class ULineBatchComponent*                            ForegroundLineBatcher;                                    // 0x0050(0x0008)
	class AGameNetworkManager*                            NetworkManager;                                           // 0x0058(0x0008)
	class UPhysicsCollisionHandler*                       PhysicsCollisionHandler;                                  // 0x0060(0x0008)
	TArray<class UObject*>                                ExtraReferencedObjects;                                   // 0x0068(0x0010)   
	TArray<class UObject*>                                PerModuleDataObjects;                                     // 0x0078(0x0010)    
	TArray<class ULevelStreaming*>                        StreamingLevels;                                          // 0x0088(0x0010)   
	unsigned char                                         UnknownData06[0x10];                                      // 0x0098(0x0010)
	class ULevel*                                         CurrentLevelPendingVisibility;                            // 0x00A8(0x0008)
	class ULevel*                                         CurrentLevelPendingInvisibility;                          // 0x00B0(0x0008)
	class UDemoNetDriver*                                 DemoNetDriver;                                            // 0x00B8(0x0008)
	class AParticleEventManager*                          MyParticleEventManager;                                   // 0x00C0(0x0008)
	class APhysicsVolume*                                 DefaultPhysicsVolume;                                     // 0x00C8(0x0008)
	unsigned char                                         UnknownData01[0x18];                                      // 0x00D0(0x0018)
	class UNavigationSystem*                              NavigationSystem;                                         // 0x00E8(0x0008)
	class AGameModeBase*                                  AuthorityGameMode;                                        // 0x00F0(0x0008)
	class AGameStateBase*                                 GameState;                                                // 0x00F8(0x0008)
	class UAISystemBase*                                  AISystem;                                                 // 0x0100(0x0008)
	class UAvoidanceManager*                              AvoidanceManager;                                         // 0x0108(0x0008)
	TArray<class ULevel*>                                 Levels;                                                   // 0x0110(0x0010)  
	TArray<struct FLevelCollection>                       LevelCollections;                                         // 0x0120(0x0010)   
	unsigned char                                         UnknownData02[0x8];                                       // 0x0130(0x0008)
	class ULevel*                                         CurrentLevel;                                             // 0x0138(0x0008)
	class UGameInstance*                                  OwningGameInstance;                                       // 0x0140(0x0008)
	TArray<class UMaterialParameterCollectionInstance*>   ParameterCollectionInstances;                             // 0x0148(0x0010)  
	class UCanvas*                                        CanvasForRenderingToTarget;                               // 0x0158(0x0008)
	class UCanvas*                                        CanvasForDrawMaterialToRenderTarget;                      // 0x0160(0x0008)
	unsigned char                                         UnknownData03[0x7D0];                                     // 0x0168(0x07D0)
	class UWorldComposition*                              WorldComposition;                                         // 0x0938(0x0008)
	unsigned char                                         UnknownData04[0x4A];                                      // 0x0940(0x004A)
	unsigned char                                         bAreConstraintsDirty : 1;                                 // 0x098A(0x0001)
	unsigned char                                         UnknownData05[0x15];                                      // 0x098B(0x0015)
};

// Class Engine.GameViewportClient
// 0x0460 (0x0490 - 0x0030)
class UGameViewportClient
{
public:
	unsigned char                                          UnknownData00[0x37];                                      // 0x0000(0x0038)
	class UConsole*                                        ViewportConsole;                                          // 0x0038(0x0008) 
	TArray<struct FDebugDisplayProperty>                   DebugProperties;                                          // 0x0040(0x0010) 
	unsigned char                                          UnknownData01[0x30];                                      // 0x0050(0x0030) 
	class UWorld*                                          World;                                                    // 0x0080(0x0008) 
	class UGameInstance*                                   GameInstance;                                             // 0x0088(0x0008) 
	unsigned char                                          charUnknownData02[0x400];                                 // 0x0090(0x0400) 
};

// Class Engine.GameInstance
class UGameInstance
{
public:
	unsigned char                                         UnknownData00[0x37];                                      // 0x0000(0x0038)
	TArray<class ULocalPlayer*>                           LocalPlayers;                                             // 0x0038(0x0010) // TArray<class ULocalPlayer*>, deref twice
	class UOnlineSession*                                 OnlineSession;                                            // 0x0048(0x0008)
	unsigned char                                         UnknownData01[0xA0];                                      // 0x0050(0x00A0)
};

// ScriptStruct CoreUObject.IntPoint
// 0x0008
struct FIntPoint
{
	int                                                  X;                                                        // 0x0000(0x0004) 
	int                                                  Y;                                                        // 0x0004(0x0004) 
};


// Class Engine.Texture2D
class UTexture2D
{
public:
	unsigned char                                      UnknownData000[0xC7];                                     // 0x0000(0x00C8)
	int                                                RequestedMips;                                            // 0x00C8(0x0004) 
	int                                                ResidentMips;                                             // 0x00CC(0x0004) 
	int                                                StreamingIndex;                                           // 0x00D0(0x0004) 
	int                                                LevelIndex;                                               // 0x00D4(0x0004) 
	int                                                FirstResourceMemMip;                                      // 0x00D8(0x0004) 
	struct FIntPoint                                   ImportedSize;                                             // 0x00DC(0x0008) 
	unsigned char                                      UnknownData00[0x4];                                       // 0x00E4(0x0004) 
	double                                             ForceMipLevelsToBeResidentTimestamp;                      // 0x00E8(0x0008) 
	unsigned char                                      bTemporarilyDisableStreaming : 1;                         // 0x00F0(0x0001) 
	unsigned char                                      bIsStreamable : 1;                                        // 0x00F0(0x0001) 
	unsigned char                                      bHasStreamingUpdatePending : 1;                           // 0x00F0(0x0001) 
	unsigned char                                      bHasCancelationPending : 1;                               // 0x00F0(0x0001) 
	unsigned char                                      bForceMiplevelsToBeResident : 1;                          // 0x00F0(0x0001) 
	unsigned char                                      bIgnoreStreamingMipBias : 1;                              // 0x00F0(0x0001) 
	unsigned char                                      bGlobalForceMipLevelsToBeResident : 1;                    // 0x00F0(0x0001) 
	unsigned char                                      UnknownData01[0x3];                                       // 0x00F1(0x0003) 
	TEnumAsByte<ETextureAddress>                       AddressX;                                                 // 0x00F4(0x0001) 
	TEnumAsByte<ETextureAddress>                       AddressY;                                                 // 0x00F5(0x0001) 
	unsigned char                                      UnknownData02[0x1A];                                      // 0x00F6(0x001A) 
};

// Class Engine.Console
class UConsole
{
public:
	unsigned char                                      UnknownData00[0x37];                                      // 0x0000(0x0038)
	class ULocalPlayer*                                ConsoleTargetPlayer;                                      // 0x0038(0x0008)
	class UTexture2D*                                  DefaultTexture_Black;                                     // 0x0040(0x0008)
	class UTexture2D*                                  DefaultTexture_White;                                     // 0x0048(0x0008)
	unsigned char                                      UnknownData01[0x18];                                      // 0x0050(0x0018)
	TArray<struct FString>                             HistoryBuffer;                                            // 0x0068(0x0010)
	unsigned char                                      UnknownData02[0xB8];                                      // 0x0078(0x00B8)
};

// Class Engine.Actor
// 0x0378 (0x03A0 - 0x0028)
class AActor : public UObject
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0028(0x0018) MISSED OFFSET
	struct FActorTickFunction                          PrimaryActorTick;                                         // 0x0040(0x0058) (CPF_Edit, CPF_DisableEditOnInstance)
	float                                              CustomTimeDilation;                                       // 0x0098(0x0004) (CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      bHidden : 1;                                              // 0x009C(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net)
	unsigned char                                      bNetTemporary : 1;                                        // 0x009C(0x0001)
	unsigned char                                      bNetStartup : 1;                                          // 0x009C(0x0001)
	unsigned char                                      bOnlyRelevantToOwner : 1;                                 // 0x009C(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_DisableEditOnInstance)
	unsigned char                                      bAlwaysRelevant : 1;                                      // 0x009C(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_DisableEditOnInstance)
	unsigned char                                      bReplicateMovement : 1;                                   // 0x009C(0x0001) (CPF_Edit, CPF_Net, CPF_DisableEditOnInstance)
	unsigned char                                      bTearOff : 1;                                             // 0x009C(0x0001) (CPF_Net)
	unsigned char                                      bExchangedRoles : 1;                                      // 0x009C(0x0001) (CPF_Transient)
	unsigned char                                      bPendingNetUpdate : 1;                                    // 0x009D(0x0001) (CPF_Transient)
	unsigned char                                      bNetLoadOnClient : 1;                                     // 0x009D(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      bNetUseOwnerRelevancy : 1;                                // 0x009D(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_DisableEditOnInstance)
	unsigned char                                      bBlockInput : 1;                                          // 0x009D(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData01 : 1;                                        // 0x009D(0x0001)
	unsigned char                                      bAllowTickBeforeBeginPlay : 1;                            // 0x009D(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData02 : 2;                                        // 0x009D(0x0001)
	unsigned char                                      UnknownData03 : 1;                                        // 0x009E(0x0001)
	unsigned char                                      bActorEnableCollision : 1;                                // 0x009E(0x0001)
	unsigned char                                      UnknownData04 : 1;                                        // 0x009E(0x0001)
	unsigned char                                      bReplicates : 1;                                          // 0x009E(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData05[0x1];                                       // 0x009F(0x0001) MISSED OFFSET
	struct FName                                       NetDriverName;                                            // 0x00A0(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<ENetRole>                              RemoteRole;                                               // 0x00A8(0x0001) (CPF_Net, CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData06[0x7];                                       // 0x00A9(0x0007) MISSED OFFSET
	class AActor*                                      Owner;                                                    // 0x00B0(0x0008) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char	                                   ReplicatedMovement[0x0034];                                       // 0x00B8(0x0034) struct FRepMovement (CPF_Edit, CPF_Net, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData07[0x4];                                       // 0x00EC(0x0004) MISSED OFFSET
	unsigned char		                               AttachmentReplication[0x0040];                                    // 0x00F0(0x0040) struct FRepAttachment (CPF_Net, CPF_Transient)
	TEnumAsByte<ENetRole>                              Role;                                                     // 0x0130(0x0001) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData08[0x2];                                       // 0x0131(0x0002) MISSED OFFSET
	TEnumAsByte<EAutoReceiveInput>                     AutoReceiveInput;                                         // 0x0133(0x0001) (CPF_Edit, CPF_ZeroConstructor, CPF_IsPlainOldData)
	int                                                InputPriority;                                            // 0x0134(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UInputComponent*                             InputComponent;                                           // 0x0138(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	TEnumAsByte<EInputConsumeOptions>                  InputConsumeOption;                                       // 0x0140(0x0001) (CPF_ZeroConstructor, CPF_Deprecated, CPF_IsPlainOldData)
	unsigned char                                      UnknownData09[0x3];                                       // 0x0141(0x0003) MISSED OFFSET
	float                                              NetCullDistanceSquared;                                   // 0x0144(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	int                                                NetTag;                                                   // 0x0148(0x0004) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	float                                              NetUpdateTime;                                            // 0x014C(0x0004) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	float                                              NetUpdateFrequency;                                       // 0x0150(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              MinNetUpdateFrequency;                                    // 0x0154(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              NetPriority;                                              // 0x0158(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              LastNetUpdateTime;                                        // 0x015C(0x0004) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      bAutoDestroyWhenFinished : 1;                             // 0x0160(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bCanBeDamaged : 1;                                        // 0x0160(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_Net, CPF_SaveGame)
	unsigned char                                      bActorIsBeingDestroyed : 1;                               // 0x0160(0x0001) (CPF_Transient, CPF_DuplicateTransient)
	unsigned char                                      bCollideWhenPlacing : 1;                                  // 0x0160(0x0001)
	unsigned char                                      bFindCameraComponentWhenViewTarget : 1;                   // 0x0160(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bRelevantForNetworkReplays : 1;                           // 0x0160(0x0001)
	unsigned char                                      bGenerateOverlapEventsDuringLevelStreaming : 1;           // 0x0160(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	TEnumAsByte<ESpawnActorCollisionHandlingMethod>    SpawnCollisionHandlingMethod;                             // 0x0161(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData10[0x6];                                       // 0x0162(0x0006) MISSED OFFSET
	class APawn*                                       Instigator;                                               // 0x0168(0x0008) (CPF_BlueprintVisible, CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TArray<class AActor*>                              Children;                                                 // 0x0170(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	class USceneComponent*                             RootComponent;                                            // 0x0180(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	TArray<class AMatineeActor*>                       ControllingMatineeActors;                                 // 0x0188(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	float                                              InitialLifeSpan;                                          // 0x0198(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData11[0xC];                                       // 0x019C(0x000C) MISSED OFFSET
	TArray<struct FName>                               Layers;                                                   // 0x01A8(0x0010) (CPF_ZeroConstructor)
	unsigned char									   ParentComponentActor[0x8];                                // 0x01B8(0x0008) TWeakObjectPtr<class AActor> (CPF_ZeroConstructor, CPF_Deprecated, CPF_IsPlainOldData)
	unsigned char							           ParentComponent[0x8];                                     // 0x01C0(0x0008) TWeakObjectPtr<class UChildActorComponent> (CPF_ExportObject, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      bAllowReceiveTickEventOnDedicatedServer : 1;              // 0x01C8(0x0001)
	unsigned char                                      UnknownData12 : 3;                                        // 0x01C8(0x0001)
	unsigned char                                      bActorSeamlessTraveled : 1;                               // 0x01C8(0x0001)
	unsigned char                                      bIgnoresOriginShifting : 1;                               // 0x01C8(0x0001) (CPF_Edit)
	unsigned char                                      bEnableAutoLODGeneration : 1;                             // 0x01C8(0x0001) (CPF_Edit)
	unsigned char                                      UnknownData13[0x7];                                       // 0x01C9(0x0007) MISSED OFFSET
	TArray<struct FName>                               Tags;                                                     // 0x01D0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor)
	uint64_t                                           HiddenEditorViews;                                        // 0x01E0(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	struct FScriptMulticastDelegate                    OnTakeAnyDamage;                                          // 0x01E8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnTakePointDamage;                                        // 0x01F8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnActorBeginOverlap;                                      // 0x0208(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnActorEndOverlap;                                        // 0x0218(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnBeginCursorOver;                                        // 0x0228(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnEndCursorOver;                                          // 0x0238(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnClicked;                                                // 0x0248(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnReleased;                                               // 0x0258(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnInputTouchBegin;                                        // 0x0268(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnInputTouchEnd;                                          // 0x0278(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnInputTouchEnter;                                        // 0x0288(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnInputTouchLeave;                                        // 0x0298(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnActorHit;                                               // 0x02A8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnDestroyed;                                              // 0x02B8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnEndPlay;                                                // 0x02C8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	unsigned char                                      UnknownData14[0xA0];                                      // 0x02D8(0x00A0) MISSED OFFSET
	TArray<class UActorComponent*>                     BlueprintCreatedComponents;                               // 0x0378(0x0010) (CPF_ExportObject, CPF_ZeroConstructor)
	TArray<class UActorComponent*>                     InstanceComponents;                                       // 0x0388(0x0010) (CPF_ExportObject, CPF_ZeroConstructor)
	unsigned char                                      UnknownData15[0x8];                                       // 0x0398(0x0008) MISSED OFFSET

public:
	inline bool IsPlayer(std::string &name) {
		if (name == "PlayerFemale_A" || name == "PlayerFemale_A_C" || name == "PlayerMale_A" || name == "PlayerMale_A_C")
			return true;

		return false;
	}

	inline bool IsVehicle()
	{
		switch (ObjectFlags)
		{
			/*UAZ*/
		case 76152:
		case 76156:
		case 76166:
		case 76165:
		case 76169:
			return true;
			/*Dacia*/
		case 75657:
		case 75653:
		case 75665:
		case 75679:
		case 75675:
			return true;

			/*Buggy*/
		case 75371:
		case 75375:
		case 75379:
		case 75401:
			return true;

			/*Jeep*/
		case 76157:
			return true;

			/*Boat*/
		case 75301:
			return true;

			/*Motorbike*/
		case 75820:
			return true;

		default:
			return false;
		}
	}
};

// Class Engine.Level
class ULevel
{
public:
	unsigned char                                      UnknownData00[0x9F];                                      // 0x0000(0x00A0) MISSED OFFSET
	TArray<class AActor*>							   AActors;													 // 0x00A0(0x0010)		
	class UWorld*                                      OwningWorld;                                              // 0x00B0(0x0008) 
	class UModel*                                      Model;                                                    // 0x00B8(0x0008) 
	TArray<class UModelComponent*>                     ModelComponents;                                          // 0x00C0(0x0010) 
	int                                                NumTextureStreamingUnbuiltComponents;                     // 0x00D0(0x0004) 
	int                                                NumTextureStreamingDirtyResources;                        // 0x00D4(0x0004) 
	class ALevelScriptActor*                           LevelScriptActor;                                         // 0x00D8(0x0008) 
	class ANavigationObjectBase*                       NavListStart;                                             // 0x00E0(0x0008) 
	class ANavigationObjectBase*                       NavListEnd;                                               // 0x00E8(0x0008) 
	TArray<class UNavigationDataChunk*>                NavDataChunks;                                            // 0x00F0(0x0010) 
	float                                              LightmapTotalSize;                                        // 0x0100(0x0004) 
	float                                              ShadowmapTotalSize;                                       // 0x0104(0x0004) 
	TArray<class Vector3D>                             StaticNavigableGeometry;                                  // 0x0108(0x0010) 
	TArray<struct FGuid>                               StreamingTextureGuids;                                    // 0x0118(0x0010) 
	unsigned char                                      UnknownData01[0x90];                                      // 0x0128(0x0090) 
	unsigned char                                      bIsLightingScenario : 1;                                  // 0x01B8(0x0001) 
	unsigned char                                      UnknownData02[0x3];                                       // 0x01B9(0x0003) 
	struct FGuid                                       LevelBuildDataId;                                         // 0x01BC(0x0010) 
	unsigned char                                      UnknownData03[0x4];                                       // 0x01CC(0x0004) 
	class UMapBuildDataRegistry*                       MapBuildData;                                             // 0x01D0(0x0008) 
	struct FIntVector                                  LightBuildLevelOffset;                                    // 0x01D8(0x000C) 
	unsigned char                                      bTextureStreamingRotationChanged : 1;                     // 0x01E4(0x0001)
	unsigned char                                      bIsVisible : 1;                                           // 0x01E4(0x0001) 
	unsigned char                                      bLocked : 1;                                              // 0x01E4(0x0001)
	unsigned char                                      UnknownData04[0xFB];                                      // 0x01E5(0x00FB) 
	class AWorldSettings*                              WorldSettings;                                            // 0x02E0(0x0008) 
	unsigned char                                      UnknownData05[0x8];                                       // 0x02E8(0x0008) 
	TArray<class UAssetUserData*>                      AssetUserData;                                            // 0x02F0(0x0010) 
	unsigned char                                      UnknownData06[0x10];                                      // 0x0300(0x0010) MISSED OFFSET
};

// Class Engine.ActorComponent
// 0x00D0 (0x00F8 - 0x0028)
class UActorComponent : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	//struct FActorComponentTickFunction                 PrimaryComponentTick;                                     // 0x0030(0x0058) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char									   PrimaryComponentTick[0x0058];
	TArray<struct FName>                               ComponentTags;                                            // 0x0088(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor)
	TArray<class UAssetUserData*>                      AssetUserData;                                            // 0x0098(0x0010) (CPF_ExportObject, CPF_ZeroConstructor)
	unsigned char                                      UnknownData01 : 3;                                        // 0x00A8(0x0001)
	unsigned char                                      bReplicates : 1;                                          // 0x00A8(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_DisableEditOnInstance)
	unsigned char                                      bNetAddressable : 1;                                      // 0x00A8(0x0001)
	unsigned char                                      UnknownData02 : 3;                                        // 0x00A8(0x0001)
	unsigned char                                      UnknownData03 : 7;                                        // 0x00A9(0x0001)
	unsigned char                                      bCreatedByConstructionScript : 1;                         // 0x00A9(0x0001) (CPF_Deprecated)
	unsigned char                                      bInstanceComponent : 1;                                   // 0x00AA(0x0001) (CPF_Deprecated)
	unsigned char                                      bAutoActivate : 1;                                        // 0x00AA(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly)
	unsigned char                                      bIsActive : 1;                                            // 0x00AA(0x0001) (CPF_Net, CPF_Transient)
	unsigned char                                      bEditableWhenInherited : 1;                               // 0x00AA(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData04 : 1;                                        // 0x00AA(0x0001)
	unsigned char                                      bCanEverAffectNavigation : 1;                             // 0x00AA(0x0001) (CPF_Edit)
	unsigned char                                      UnknownData05 : 2;                                        // 0x00AA(0x0001)
	unsigned char                                      bIsEditorOnly : 1;                                        // 0x00AB(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly)
	unsigned char                                      UnknownData06[0x4];                                       // 0x00AC(0x0004) MISSED OFFSET
	//TEnumAsByte<EComponentCreationMethod>              CreationMethod;                                         // 0x00B0(0x0001) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char									   CreationMethod;
	unsigned char                                      UnknownData07[0xF];                                       // 0x00B1(0x000F) MISSED OFFSET
	TArray<struct FSimpleMemberReference>              UCSModifiedProperties;                                    // 0x00C0(0x0010) (CPF_ZeroConstructor)
	struct FScriptMulticastDelegate                    OnComponentActivated;                                     // 0x00D0(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnComponentDeactivated;                                   // 0x00E0(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	unsigned char                                      UnknownData08[0x8];                                       // 0x00F0(0x0008) MISSED OFFSET
};

class USceneComponent : public UActorComponent
{
public:
	class USceneComponent*                             AttachParent;                                             // 0x00F8(0x0008) (CPF_ExportObject, CPF_Net, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	TArray<class USceneComponent*>                     AttachChildren;                                           // 0x0100(0x0010) (CPF_ExportObject, CPF_Net, CPF_ZeroConstructor, CPF_Transient)
	unsigned char                                      UnknownData00[0x50];                                      // 0x0110(0x0050) UNKNOWN PROPERTY: SetProperty Engine.SceneComponent.ClientAttachedChildren
	struct FName                                       AttachSocketName;                                         // 0x0160(0x0008) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01 : 1;                                        // 0x0168(0x0001)
	unsigned char                                      bReplicatesAttachmentReference : 1;                       // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_DisableEditOnInstance)
	unsigned char                                      bReplicatesAttachment : 1;                                // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_DisableEditOnInstance)
	unsigned char                                      bWorldToComponentUpdated : 1;                             // 0x0168(0x0001) (CPF_Transient)
	unsigned char                                      bAbsoluteLocation : 1;                                    // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_Net)
	unsigned char                                      bAbsoluteRotation : 1;                                    // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_Net)
	unsigned char                                      bAbsoluteScale : 1;                                       // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_Net)
	unsigned char                                      bVisible : 1;                                             // 0x0168(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net)
	unsigned char                                      bHiddenInGame : 1;                                        // 0x0169(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly)
	unsigned char                                      bShouldUpdatePhysicsVolume : 1;                           // 0x0169(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bBoundsChangeTriggersStreamingDataRebuild : 1;            // 0x0169(0x0001)
	unsigned char                                      bUseAttachParentBound : 1;                                // 0x0169(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData02 : 2;                                        // 0x0169(0x0001)
	unsigned char                                      bAbsoluteTranslation : 1;                                 // 0x0169(0x0001) (CPF_Deprecated)
	unsigned char                                      UnknownData03[0x2];                                       // 0x016A(0x0002) MISSED OFFSET
	unsigned char                                      PhysicsVolume[0x8];										 // 0x016C(0x0008) TWeakObjectPtr<class APhysicsVolume> (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData04[0x6C];                                      // 0x0174(0x006C) MISSED OFFSET
	class Vector3D                                     RelativeLocation;                                         // 0x01E0(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Rotator                                      RelativeRotation;										 // 0x01EC(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData05[0x28];                                      // 0x01F8(0x0028) MISSED OFFSET
	class Vector3D                                     RelativeScale3D;                                          // 0x0220(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Vector3D                                     RelativeTranslation;                                      // 0x022C(0x000C) (CPF_ZeroConstructor, CPF_Deprecated, CPF_IsPlainOldData)
	TEnumAsByte<EComponentMobility>                    Mobility;                                               // 0x0238(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<EDetailMode>                           DetailMode;                                             // 0x0239(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData06[0x1E];                                      // 0x023A(0x001E) MISSED OFFSET
	class Vector3D                                     ComponentVelocity;                                        // 0x0258(0x000C) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData07[0x4];                                       // 0x0264(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate                    PhysicsVolumeChangedDelegate;                             // 0x0268(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
	unsigned char                                      UnknownData08[0x88];                                      // 0x0278(0x0088) MISSED OFFSET
};


// Class Engine.Controller
// 0x0068 (0x0408 - 0x03A0)
class AController : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03A0(0x0008) MISSED OFFSET
	class APawn*                                       Pawn;                                                     // 0x03A8(0x0008) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x03B0(0x0008) MISSED OFFSET
	class ACharacter*                                  Character;                                                // 0x03B8(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class APlayerState*                                PlayerState;                                              // 0x03C0(0x0008) (CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class USceneComponent*                             TransformComponent;                                       // 0x03C8(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	class Rotator                                      ControlRotation;                                          // 0x03D0(0x000C) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      bAttachToPawn : 1;                                        // 0x03DC(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      bIsPlayerController : 1;                                  // 0x03DC(0x0001)
	unsigned char                                      UnknownData02[0x13];                                      // 0x03DD(0x0013) MISSED OFFSET
	struct FName                                       StateName;                                                // 0x03F0(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FScriptMulticastDelegate                    OnInstigatedAnyDamage;                                    // 0x03F8(0x0010) (CPF_ZeroConstructor, CPF_InstancedReference, CPF_BlueprintAssignable)
};

// ScriptStruct Engine.WeightedBlendables
// 0x0010
struct FWeightedBlendables
{
	TArray<struct FWeightedBlendable>                  Array;                                                    // 0x0000(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor)
};

// ScriptStruct Engine.PostProcessSettings
// 0x04E0
struct FPostProcessSettings
{
	unsigned char                                      bOverride_WhiteTemp : 1;                                  // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_WhiteTint : 1;                                  // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorSaturation : 1;                            // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorContrast : 1;                              // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGamma : 1;                                 // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGain : 1;                                  // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorOffset : 1;                                // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorSaturationShadows : 1;                     // 0x0000(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorContrastShadows : 1;                       // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGammaShadows : 1;                          // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGainShadows : 1;                           // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorOffsetShadows : 1;                         // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorSaturationMidtones : 1;                    // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorContrastMidtones : 1;                      // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGammaMidtones : 1;                         // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGainMidtones : 1;                          // 0x0001(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorOffsetMidtones : 1;                        // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorSaturationHighlights : 1;                  // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorContrastHighlights : 1;                    // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGammaHighlights : 1;                       // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGainHighlights : 1;                        // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorOffsetHighlights : 1;                      // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorCorrectionShadowsMax : 1;                  // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorCorrectionHighlightsMin : 1;               // 0x0002(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmWhitePoint : 1;                             // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmSaturation : 1;                             // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmChannelMixerRed : 1;                        // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmChannelMixerGreen : 1;                      // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmChannelMixerBlue : 1;                       // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmContrast : 1;                               // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmDynamicRange : 1;                           // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmHealAmount : 1;                             // 0x0003(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmToeAmount : 1;                              // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmShadowTint : 1;                             // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmShadowTintBlend : 1;                        // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmShadowTintAmount : 1;                       // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmSlope : 1;                                  // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmToe : 1;                                    // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmShoulder : 1;                               // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmBlackClip : 1;                              // 0x0004(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_FilmWhiteClip : 1;                              // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_SceneColorTint : 1;                             // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_SceneFringeIntensity : 1;                       // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientCubemapTint : 1;                         // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientCubemapIntensity : 1;                    // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomIntensity : 1;                             // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomThreshold : 1;                             // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom1Tint : 1;                                 // 0x0005(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom1Size : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom2Size : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom2Tint : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom3Tint : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom3Size : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom4Tint : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom4Size : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom5Tint : 1;                                 // 0x0006(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom5Size : 1;                                 // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom6Tint : 1;                                 // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_Bloom6Size : 1;                                 // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomSizeScale : 1;                             // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomDirtMaskIntensity : 1;                     // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomDirtMaskTint : 1;                          // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_BloomDirtMask : 1;                              // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureMethod : 1;                         // 0x0007(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureLowPercent : 1;                     // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureHighPercent : 1;                    // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureMinBrightness : 1;                  // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureMaxBrightness : 1;                  // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureSpeedUp : 1;                        // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureSpeedDown : 1;                      // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AutoExposureBias : 1;                           // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_HistogramLogMin : 1;                            // 0x0008(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_HistogramLogMax : 1;                            // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareIntensity : 1;                         // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareTint : 1;                              // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareTints : 1;                             // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareBokehSize : 1;                         // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareBokehShape : 1;                        // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LensFlareThreshold : 1;                         // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_VignetteIntensity : 1;                          // 0x0009(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_GrainIntensity : 1;                             // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_GrainJitter : 1;                                // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionIntensity : 1;                  // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionStaticFraction : 1;             // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionRadius : 1;                     // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionFadeDistance : 1;               // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionFadeRadius : 1;                 // 0x000A(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAOPowerExponent : 1;                          // 0x000A(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAORadius : 1;                                 // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAOBias : 1;                                   // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAODetailAO : 1;                               // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAOBlurRadius : 1;                             // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAOBlurSharpness : 1;                          // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAOMaxViewDepth : 1;                           // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_HBAODepthSharpness : 1;                         // 0x000B(0x0001) (CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionDistance : 1;                   // 0x000B(0x0001) (CPF_Deprecated)
	unsigned char                                      bOverride_AmbientOcclusionRadiusInWS : 1;                 // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionPower : 1;                      // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionBias : 1;                       // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionQuality : 1;                    // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionMipBlend : 1;                   // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionMipScale : 1;                   // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_AmbientOcclusionMipThreshold : 1;               // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVIntensity : 1;                               // 0x000C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVDirectionalOcclusionIntensity : 1;           // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVDirectionalOcclusionRadius : 1;              // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVDiffuseOcclusionExponent : 1;                // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVSpecularOcclusionExponent : 1;               // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVDiffuseOcclusionIntensity : 1;               // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVSpecularOcclusionIntensity : 1;              // 0x000D(0x0001) (CPF_Edit)
	unsigned char                                      bOverride_LPVSize : 1;                                    // 0x000D(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVSecondaryOcclusionIntensity : 1;             // 0x000D(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVSecondaryBounceIntensity : 1;                // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVGeometryVolumeBias : 1;                      // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVVplInjectionBias : 1;                        // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_LPVEmissiveInjectionIntensity : 1;              // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_IndirectLightingColor : 1;                      // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_IndirectLightingIntensity : 1;                  // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGradingIntensity : 1;                      // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ColorGradingLUT : 1;                            // 0x000E(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldFocalDistance : 1;                  // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldFstop : 1;                          // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldSensorWidth : 1;                    // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldDepthBlurRadius : 1;                // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldDepthBlurAmount : 1;                // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldFocalRegion : 1;                    // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldNearTransitionRegion : 1;           // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldFarTransitionRegion : 1;            // 0x000F(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldScale : 1;                          // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldMaxBokehSize : 1;                   // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldNearBlurSize : 1;                   // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldFarBlurSize : 1;                    // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldMethod : 1;                         // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_MobileHQGaussian : 1;                           // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldBokehShape : 1;                     // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldOcclusion : 1;                      // 0x0010(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldColorThreshold : 1;                 // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldSizeThreshold : 1;                  // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldSkyFocusDistance : 1;               // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_DepthOfFieldVignetteSize : 1;                   // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_MotionBlurAmount : 1;                           // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_MotionBlurMax : 1;                              // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_MotionBlurPerObjectSize : 1;                    // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ScreenPercentage : 1;                           // 0x0011(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ScreenSpaceReflectionIntensity : 1;             // 0x0012(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ScreenSpaceReflectionQuality : 1;               // 0x0012(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ScreenSpaceReflectionMaxRoughness : 1;          // 0x0012(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bOverride_ScreenSpaceReflectionRoughnessScale : 1;        // 0x0012(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0013(0x0001) MISSED OFFSET
	float                                              WhiteTemp;                                                // 0x0014(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              WhiteTint;                                                // 0x0018(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	struct FVector4                                    ColorSaturation;                                          // 0x0020(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorContrast;                                            // 0x0030(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGamma;                                               // 0x0040(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGain;                                                // 0x0050(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorOffset;                                              // 0x0060(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorSaturationShadows;                                   // 0x0070(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorContrastShadows;                                     // 0x0080(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGammaShadows;                                        // 0x0090(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGainShadows;                                         // 0x00A0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorOffsetShadows;                                       // 0x00B0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ColorCorrectionShadowsMax;                                // 0x00C0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData02[0xC];                                       // 0x00C4(0x000C) MISSED OFFSET
	struct FVector4                                    ColorSaturationMidtones;                                  // 0x00D0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorContrastMidtones;                                    // 0x00E0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGammaMidtones;                                       // 0x00F0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGainMidtones;                                        // 0x0100(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorOffsetMidtones;                                      // 0x0110(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorSaturationHighlights;                                // 0x0120(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorContrastHighlights;                                  // 0x0130(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGammaHighlights;                                     // 0x0140(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorGainHighlights;                                      // 0x0150(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FVector4                                    ColorOffsetHighlights;                                    // 0x0160(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ColorCorrectionHighlightsMin;                             // 0x0170(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                FilmWhitePoint;                                           // 0x0174(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                FilmShadowTint;                                           // 0x0184(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmShadowTintBlend;                                      // 0x0194(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmShadowTintAmount;                                     // 0x0198(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmSaturation;                                           // 0x019C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                FilmChannelMixerRed;                                      // 0x01A0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                FilmChannelMixerGreen;                                    // 0x01B0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                FilmChannelMixerBlue;                                     // 0x01C0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmContrast;                                             // 0x01D0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmToeAmount;                                            // 0x01D4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmHealAmount;                                           // 0x01D8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmDynamicRange;                                         // 0x01DC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmSlope;                                                // 0x01E0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmToe;                                                  // 0x01E4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmShoulder;                                             // 0x01E8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmBlackClip;                                            // 0x01EC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FilmWhiteClip;                                            // 0x01F0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                SceneColorTint;                                           // 0x01F4(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              SceneFringeIntensity;                                     // 0x0204(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              BloomIntensity;                                           // 0x0208(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              BloomThreshold;                                           // 0x020C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              BloomSizeScale;                                           // 0x0210(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom1Size;                                               // 0x0214(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom2Size;                                               // 0x0218(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom3Size;                                               // 0x021C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom4Size;                                               // 0x0220(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom5Size;                                               // 0x0224(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              Bloom6Size;                                               // 0x0228(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom1Tint;                                               // 0x022C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom2Tint;                                               // 0x023C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom3Tint;                                               // 0x024C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom4Tint;                                               // 0x025C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom5Tint;                                               // 0x026C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                Bloom6Tint;                                               // 0x027C(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              BloomDirtMaskIntensity;                                   // 0x028C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                BloomDirtMaskTint;                                        // 0x0290(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UTexture*                                    BloomDirtMask;                                            // 0x02A0(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVIntensity;                                             // 0x02A8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVVplInjectionBias;                                      // 0x02AC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVSize;                                                  // 0x02B0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVSecondaryOcclusionIntensity;                           // 0x02B4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVSecondaryBounceIntensity;                              // 0x02B8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVGeometryVolumeBias;                                    // 0x02BC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVEmissiveInjectionIntensity;                            // 0x02C0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVDirectionalOcclusionIntensity;                         // 0x02C4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVDirectionalOcclusionRadius;                            // 0x02C8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVDiffuseOcclusionExponent;                              // 0x02CC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVSpecularOcclusionExponent;                             // 0x02D0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVDiffuseOcclusionIntensity;                             // 0x02D4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LPVSpecularOcclusionIntensity;                            // 0x02D8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                AmbientCubemapTint;                                       // 0x02DC(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientCubemapIntensity;                                  // 0x02EC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UTextureCube*                                AmbientCubemap;                                           // 0x02F0(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<EAutoExposureMethod>                   AutoExposureMethod;                                       // 0x02F8(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x02F9(0x0003) MISSED OFFSET
	float                                              AutoExposureLowPercent;                                   // 0x02FC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureHighPercent;                                  // 0x0300(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureMinBrightness;                                // 0x0304(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureMaxBrightness;                                // 0x0308(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureSpeedUp;                                      // 0x030C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureSpeedDown;                                    // 0x0310(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AutoExposureBias;                                         // 0x0314(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HistogramLogMin;                                          // 0x0318(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HistogramLogMax;                                          // 0x031C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LensFlareIntensity;                                       // 0x0320(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                LensFlareTint;                                            // 0x0324(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LensFlareBokehSize;                                       // 0x0334(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              LensFlareThreshold;                                       // 0x0338(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	class UTexture*                                    LensFlareBokehShape;                                      // 0x0340(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                LensFlareTints[0x8];                                      // 0x0348(0x0010) (CPF_Edit, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              VignetteIntensity;                                        // 0x03C8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              GrainJitter;                                              // 0x03CC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              GrainIntensity;                                           // 0x03D0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAOPowerExponent;                                        // 0x03D4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAORadius;                                               // 0x03D8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAOBias;                                                 // 0x03DC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAODetailAO;                                             // 0x03E0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<EHBAOBlurRadius>                       HBAOBlurRadius;                                           // 0x03E4(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData05[0x3];                                       // 0x03E5(0x0003) MISSED OFFSET
	float                                              HBAOBlurSharpness;                                        // 0x03E8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAOMaxViewDepth;                                         // 0x03EC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HBAODepthSharpness;                                       // 0x03F0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionIntensity;                                // 0x03F4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionStaticFraction;                           // 0x03F8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionRadius;                                   // 0x03FC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      AmbientOcclusionRadiusInWS : 1;                           // 0x0400(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData06[0x3];                                       // 0x0401(0x0003) MISSED OFFSET
	float                                              AmbientOcclusionFadeDistance;                             // 0x0404(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionFadeRadius;                               // 0x0408(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionDistance;                                 // 0x040C(0x0004) (CPF_ZeroConstructor, CPF_Deprecated, CPF_IsPlainOldData)
	float                                              AmbientOcclusionPower;                                    // 0x0410(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionBias;                                     // 0x0414(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionQuality;                                  // 0x0418(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionMipBlend;                                 // 0x041C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionMipScale;                                 // 0x0420(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AmbientOcclusionMipThreshold;                             // 0x0424(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FLinearColor                                IndirectLightingColor;                                    // 0x0428(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              IndirectLightingIntensity;                                // 0x0438(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ColorGradingIntensity;                                    // 0x043C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UTexture*                                    ColorGradingLUT;                                          // 0x0440(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<EDepthOfFieldMethod>                   DepthOfFieldMethod;                                       // 0x0448(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData07[0x3];                                       // 0x0449(0x0003) MISSED OFFSET
	unsigned char                                      bMobileHQGaussian : 1;                                    // 0x044C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData08[0x3];                                       // 0x044D(0x0003) MISSED OFFSET
	float                                              DepthOfFieldFstop;                                        // 0x0450(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldSensorWidth;                                  // 0x0454(0x0004) (CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldFocalDistance;                                // 0x0458(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldDepthBlurAmount;                              // 0x045C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldDepthBlurRadius;                              // 0x0460(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldFocalRegion;                                  // 0x0464(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldNearTransitionRegion;                         // 0x0468(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldFarTransitionRegion;                          // 0x046C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldScale;                                        // 0x0470(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldMaxBokehSize;                                 // 0x0474(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldNearBlurSize;                                 // 0x0478(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldFarBlurSize;                                  // 0x047C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UTexture*                                    DepthOfFieldBokehShape;                                   // 0x0480(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldOcclusion;                                    // 0x0488(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldColorThreshold;                               // 0x048C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldSizeThreshold;                                // 0x0490(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldSkyFocusDistance;                             // 0x0494(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              DepthOfFieldVignetteSize;                                 // 0x0498(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              MotionBlurAmount;                                         // 0x049C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              MotionBlurMax;                                            // 0x04A0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              MotionBlurPerObjectSize;                                  // 0x04A4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ScreenPercentage;                                         // 0x04A8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ScreenSpaceReflectionIntensity;                           // 0x04AC(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ScreenSpaceReflectionQuality;                             // 0x04B0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ScreenSpaceReflectionMaxRoughness;                        // 0x04B4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	struct FWeightedBlendables                         WeightedBlendables;                                       // 0x04B8(0x0010) (CPF_Edit)
	TArray<class UObject*>                             Blendables;                                               // 0x04C8(0x0010) (CPF_ZeroConstructor, CPF_Deprecated)
	unsigned char                                      UnknownData09[0x8];                                       // 0x04D8(0x0008) MISSED OFFSET
};

// ScriptStruct Engine.MinimalViewInfo
// 0x0530
struct FMinimalViewInfo
{
	class Vector3D                                     Location;                                                 // 0x0000(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Rotator                                      Rotation;                                                 // 0x000C(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              FOV;                                                      // 0x0018(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              OrthoWidth;                                               // 0x001C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              OrthoNearClipPlane;                                       // 0x0020(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              OrthoFarClipPlane;                                        // 0x0024(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              AspectRatio;                                              // 0x0028(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      bConstrainAspectRatio : 1;                                // 0x002C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bUseFieldOfViewForLOD : 1;                                // 0x002C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData00[0x3];                                       // 0x002D(0x0003) MISSED OFFSET
	TEnumAsByte<ECameraProjectionMode>                 ProjectionMode;                                           // 0x0030(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	float                                              PostProcessBlendWeight;                                   // 0x0034(0x0004) (CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	struct FPostProcessSettings                        PostProcessSettings;                                      // 0x0040(0x04E0) (CPF_BlueprintVisible)
	class Vector2D                                     OffCenterProjectionOffset;                                // 0x0520(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_DisableEditOnTemplate, CPF_Transient, CPF_EditConst, CPF_IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x0528(0x0008) MISSED OFFSET
};

// ScriptStruct Engine.CameraCacheEntry
// 0x0540
struct FCameraCacheEntry
{
	float                                              TimeStamp;                                                // 0x0000(0x0004) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0004(0x000C) MISSED OFFSET
	struct FMinimalViewInfo                            POV;                                                      // 0x0010(0x0530)
};

// ScriptStruct Engine.TViewTarget
// 0x0550
struct FTViewTarget
{
	class AActor*                                      Target;                                                   // 0x0000(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0008(0x0008) MISSED OFFSET
	struct FMinimalViewInfo                            POV;                                                      // 0x0010(0x0530) (CPF_Edit, CPF_BlueprintVisible)
	class APlayerState*                                PlayerState;                                              // 0x0540(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0548(0x0008) MISSED OFFSET
};

// Class Engine.PlayerCameraManager
// 0x16C0 (0x1A60 - 0x03A0)
class APlayerCameraManager : public AActor
{
public:
	class APlayerController*                           PCOwner;                                                  // 0x03A0(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	class USceneComponent*                             TransformComponent;                                       // 0x03A8(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_ExportObject, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_EditConst, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x03B0(0x0008) MISSED OFFSET
	float                                              DefaultFOV;                                               // 0x03B8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03BC(0x0004) MISSED OFFSET
	float                                              DefaultOrthoWidth;                                        // 0x03C0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x03C4(0x0004) MISSED OFFSET
	float                                              DefaultAspectRatio;                                       // 0x03C8(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData03[0x44];                                      // 0x03CC(0x0044) MISSED OFFSET
	struct FCameraCacheEntry                           CameraCache;                                              // 0x0410(0x0540) (CPF_Transient)
	struct FCameraCacheEntry                           LastFrameCameraCache;                                     // 0x0950(0x0540) (CPF_Transient)
	struct FTViewTarget                                ViewTarget;                                               // 0x0E90(0x0550) (CPF_Transient)
	struct FTViewTarget                                PendingViewTarget;                                        // 0x13E0(0x0550) (CPF_Transient)
	unsigned char                                      UnknownData04[0x18];                                      // 0x1930(0x0018) MISSED OFFSET
	TArray<class UCameraModifier*>                     ModifierList;                                             // 0x1948(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	TArray<class UClass*>                              DefaultModifiers;                                         // 0x1958(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance)
	float                                              FreeCamDistance;                                          // 0x1968(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Vector3D                                     FreeCamOffset;                                            // 0x196C(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Vector3D                                     ViewTargetOffset;                                         // 0x1978(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData05[0x14];                                      // 0x1984(0x0014) MISSED OFFSET
	TArray<class AEmitterCameraLensEffectBase*>        CameraLensEffects;                                        // 0x1998(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	class UCameraModifier_CameraShake*                 CachedCameraShakeMod;                                     // 0x19A8(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	class UCameraAnimInst*                             AnimInstPool[0x8];                                        // 0x19B0(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	TArray<struct FPostProcessSettings>                PostProcessBlendCache;                                    // 0x19F0(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	unsigned char                                      UnknownData06[0x10];                                      // 0x1A00(0x0010) MISSED OFFSET
	TArray<class UCameraAnimInst*>                     ActiveAnims;                                              // 0x1A10(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	TArray<class UCameraAnimInst*>                     FreeAnims;                                                // 0x1A20(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	class ACameraActor*                                AnimCameraActor;                                          // 0x1A30(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      bIsOrthographic : 1;                                      // 0x1A38(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData07 : 5;                                        // 0x1A38(0x0001)
	unsigned char                                      bUseClientSideCameraUpdates : 1;                          // 0x1A38(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly)
	unsigned char                                      UnknownData08[0x3];                                       // 0x1A39(0x0003) MISSED OFFSET
	float                                              ViewPitchMin;                                             // 0x1A3C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ViewPitchMax;                                             // 0x1A40(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ViewYawMin;                                               // 0x1A44(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ViewYawMax;                                               // 0x1A48(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ViewRollMin;                                              // 0x1A4C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              ViewRollMax;                                              // 0x1A50(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData09[0xC];                                       // 0x1A54(0x000C) MISSED OFFSET
};
// Class Engine.PlayerController
// 0x02C8 (0x06D0 - 0x0408)
class APlayerController : public AController
{
public:
	class UPlayer*                                     Player;                                                   // 0x0408(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0410(0x0008) MISSED OFFSET
	class APawn*                                       AcknowledgedPawn;                                         // 0x0418(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UInterpTrackInstDirector*                    ControllingDirTrackInst;                                  // 0x0420(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0428(0x0008) MISSED OFFSET
	class AHUD*                                        MyHUD;                                                    // 0x0430(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class APlayerCameraManager*                        PlayerCameraManager;                                      // 0x0438(0x0008) (CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UClass*                                      PlayerCameraManagerClass;                                 // 0x0440(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	bool                                               bAutoManageActiveCameraTarget;                            // 0x0448(0x0001) (CPF_Edit, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0449(0x0003) MISSED OFFSET
	class Rotator                                      TargetViewRotation;                                       // 0x044C(0x000C) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData03[0xC];                                       // 0x0458(0x000C) MISSED OFFSET
	float                                              SmoothTargetViewRotationSpeed;                            // 0x0464(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TArray<class AActor*>                              HiddenActors;                                             // 0x0468(0x0010) (CPF_ZeroConstructor)
	float                                              LastSpectatorStateSynchTime;                              // 0x0478(0x0004) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Vector3D                                     LastSpectatorSyncLocation;                                // 0x047C(0x000C) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	class Rotator                                      LastSpectatorSyncRotation;                                // 0x0488(0x000C) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	int                                                ClientCap;                                                // 0x0494(0x0004) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class UCheatManager*                               CheatManager;                                             // 0x0498(0x0008) (CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	class UClass*                                      CheatClass;                                               // 0x04A0(0x0008) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	class UPlayerInput*                                PlayerInput;                                              // 0x04A8(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	TArray<struct FActiveForceFeedbackEffect>          ActiveForceFeedbackEffects;                               // 0x04B0(0x0010) (CPF_ZeroConstructor, CPF_Transient)
	unsigned char                                      UnknownData04[0x80];                                      // 0x04C0(0x0080) MISSED OFFSET
	unsigned char                                      UnknownData05 : 3;                                        // 0x0540(0x0001)
	unsigned char                                      bPlayerIsWaiting : 1;                                     // 0x0540(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_DisableEditOnTemplate, CPF_EditConst)
	unsigned char                                      UnknownData06[0x3];                                       // 0x0541(0x0003) MISSED OFFSET
	unsigned char                                      NetPlayerIndex;                                           // 0x0544(0x0001) (CPF_ZeroConstructor, CPF_DuplicateTransient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData07[0x3B];                                      // 0x0545(0x003B) MISSED OFFSET
	class UNetConnection*                              PendingSwapConnection;                                    // 0x0580(0x0008) (CPF_ZeroConstructor, CPF_DuplicateTransient, CPF_IsPlainOldData)
	class UNetConnection*                              NetConnection;                                            // 0x0588(0x0008) (CPF_ZeroConstructor, CPF_DuplicateTransient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData08[0xC];                                       // 0x0590(0x000C) MISSED OFFSET
	float                                              InputYawScale;                                            // 0x059C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_Config, CPF_IsPlainOldData)
	float                                              InputPitchScale;                                          // 0x05A0(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_Config, CPF_IsPlainOldData)
	float                                              InputRollScale;                                           // 0x05A4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_Config, CPF_IsPlainOldData)
	unsigned char                                      bShowMouseCursor : 1;                                     // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bEnableClickEvents : 1;                                   // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bEnableTouchEvents : 1;                                   // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bEnableMouseOverEvents : 1;                               // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bEnableTouchOverEvents : 1;                               // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      bForceFeedbackEnabled : 1;                                // 0x05A8(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	unsigned char                                      UnknownData09[0x7];                                       // 0x05A9(0x0007) MISSED OFFSET
	TArray<struct FKey>                                ClickEventKeys;                                           // 0x05B0(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor)
	TEnumAsByte<EMouseCursor>                          DefaultMouseCursor;                                       // 0x05C0(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<EMouseCursor>                          CurrentMouseCursor;                                       // 0x05C1(0x0001) (CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     DefaultClickTraceChannel;                                 // 0x05C2(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     CurrentClickTraceChannel;                                 // 0x05C3(0x0001) (CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float                                              HitResultTraceDistance;                                   // 0x05C4(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData10[0x80];                                      // 0x05C8(0x0080) MISSED OFFSET
	class UInputComponent*                             InactiveStateInputComponent;                              // 0x0648(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      UnknownData11[0x18];                                      // 0x0650(0x0018) MISSED OFFSET
	class UTouchInterface*                             CurrentTouchInterface;                                    // 0x0668(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData12[0x40];                                      // 0x0670(0x0040) MISSED OFFSET
	class ASpectatorPawn*                              SpectatorPawn;                                            // 0x06B0(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	class Vector3D                                     SpawnLocation;                                            // 0x06B8(0x000C) (CPF_Net, CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData13[0x4];                                       // 0x06C4(0x0004) MISSED OFFSET
	bool                                               bIsLocalPlayerController;                                 // 0x06C8(0x0001) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData14[0x1];                                       // 0x06C9(0x0001) MISSED OFFSET
	uint16_t                                           SeamlessTravelCount;                                      // 0x06CA(0x0002) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	uint16_t                                           LastCompletedSeamlessTravelCount;                         // 0x06CC(0x0002) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData15[0x2];                                       // 0x06CE(0x0002) MISSED OFFSET
};
// Class Engine.Player
// 0x0020 (0x0048 - 0x0028)
class UPlayer : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	class APlayerController*                           PlayerController;                                         // 0x0030(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	int                                                CurrentNetSpeed;                                          // 0x0038(0x0004) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	int                                                ConfiguredInternetSpeed;                                  // 0x003C(0x0004) (CPF_ZeroConstructor, CPF_Config, CPF_GlobalConfig, CPF_IsPlainOldData)
	int                                                ConfiguredLanSpeed;                                       // 0x0040(0x0004) (CPF_ZeroConstructor, CPF_Config, CPF_GlobalConfig, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0044(0x0004) MISSED OFFSET
};

// Class Engine.LocalPlayer
// 0x0148 (0x0190 - 0x0048)
class ULocalPlayer : public UPlayer
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0048(0x0010) MISSED OFFSET
	class UGameViewportClient*                         ViewportClient;                                           // 0x0058(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0060(0x0020) MISSED OFFSET
	class UClass*                                      PendingLevelPlayerControllerClass;                        // 0x0080(0x0008) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char                                      bSentSplitJoin : 1;                                       // 0x0088(0x0001) (CPF_Edit, CPF_Transient, CPF_EditConst)
	unsigned char                                      UnknownData02[0x107];                                     // 0x0089(0x0107) MISSED OFFSET
};

