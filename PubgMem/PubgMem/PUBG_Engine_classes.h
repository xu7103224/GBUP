#pragma once
#include "PUBG_Basic.h"
#include "PUBG_Engine_structs.h"
class UGameInstance;
class UConsole;
class ULevel;



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

// Class Engine.LocalPlayer
class ULocalPlayer
{
public:
	unsigned char                                         UnknownData00[0x57];                                      // 0x0000(0x0058) 
	class UGameViewportClient*                            ViewportClient;                                           // 0x0058(0x0008) 
	unsigned char                                         UnknownData01[0x20];                                      // 0x0060(0x0020) 
	class UClass*                                         PendingLevelPlayerControllerClass;                        // 0x0080(0x0008) 
	unsigned char                                         bSentSplitJoin : 1;                                       // 0x0088(0x0001) 
	unsigned char                                         UnknownData02[0x107];                                     // 0x0089(0x0107) 
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
class AActor
{
public:
	uint64_t                                           BasePointer;                                              // 0x0000(0x0008)
	uint64_t                                           unknowDWORD;                                              // 0x0008(0x0008)
	int                                                ObjectFlags;                                              // 0x0010(0x0004)
	int                                                Id;                                                       // 0x0014(0x0004)
	int                                                Id2;                                                      // 0x0018(0x0004)
	unsigned char                                      UnknownData00[0x24];                                      // 0x001C(0x0024) MISSED OFFSET
	struct FActorTickFunction                          PrimaryActorTick;                                         // 0x0040(0x0058) 
	float                                              CustomTimeDilation;                                       // 0x0098(0x0004) 
	unsigned char                                      bHidden : 1;                                              // 0x009C(0x0001) 
	unsigned char                                      bNetTemporary : 1;                                        // 0x009C(0x0001)
	unsigned char                                      bNetStartup : 1;                                          // 0x009C(0x0001)
	unsigned char                                      bOnlyRelevantToOwner : 1;                                 // 0x009C(0x0001) 
	unsigned char                                      bAlwaysRelevant : 1;                                      // 0x009C(0x0001) 
	unsigned char                                      bReplicateMovement : 1;                                   // 0x009C(0x0001) 
	unsigned char                                      bTearOff : 1;                                             // 0x009C(0x0001) 
	unsigned char                                      bExchangedRoles : 1;                                      // 0x009C(0x0001) 
	unsigned char                                      bPendingNetUpdate : 1;                                    // 0x009D(0x0001) 
	unsigned char                                      bNetLoadOnClient : 1;                                     // 0x009D(0x0001) 
	unsigned char                                      bNetUseOwnerRelevancy : 1;                                // 0x009D(0x0001) 
	unsigned char                                      bBlockInput : 1;                                          // 0x009D(0x0001) 
	unsigned char                                      bAllowTickBeforeBeginPlay : 1;                            // 0x009D(0x0001) 
	unsigned char                                      bActorEnableCollision : 1;                                // 0x009E(0x0001)
	unsigned char                                      bReplicates : 1;                                          // 0x009E(0x0001) 
	unsigned char                                      UnknownData01[0x1];                                       // 0x009F(0x0001) 
	struct FName                                       NetDriverName;                                            // 0x00A0(0x0008) 
	TEnumAsByte<ENetRole>                              RemoteRole;                                               // 0x00A8(0x0001) 
	unsigned char                                      UnknownData02[0x7];                                       // 0x00A9(0x0007) 
	class AActor*                                      Owner;                                                    // 0x00B0(0x0008) 
	unsigned char                                      ReplicatedMovement[0x34];                                 // 0x00B8(0x0034)  struct FRepMovement
	unsigned char                                      UnknownData03[0x4];                                       // 0x00EC(0x0004) 
	unsigned char                                      AttachmentReplication[0x40];                              // 0x00F0(0x0040)  struct FRepAttachment 
	TEnumAsByte<ENetRole>                              Role;                                                     // 0x0130(0x0001) 
	unsigned char                                      UnknownData04[0x2];                                       // 0x0131(0x0002) 
	TEnumAsByte<EAutoReceiveInput>                     AutoReceiveInput;                                         // 0x0133(0x0001) 
	int                                                InputPriority;                                            // 0x0134(0x0004) 
	class UInputComponent*                             InputComponent;                                           // 0x0138(0x0008) 
	TEnumAsByte<EInputConsumeOptions>                  InputConsumeOption;                                       // 0x0140(0x0001) 
	unsigned char                                      UnknownData05[0x3];                                       // 0x0141(0x0003) 
	float                                              NetCullDistanceSquared;                                   // 0x0144(0x0004) 
	int                                                NetTag;                                                   // 0x0148(0x0004) 
	float                                              NetUpdateTime;                                            // 0x014C(0x0004) 
	float                                              NetUpdateFrequency;                                       // 0x0150(0x0004) 
	float                                              MinNetUpdateFrequency;                                    // 0x0154(0x0004) 
	float                                              NetPriority;                                              // 0x0158(0x0004) 
	float                                              LastNetUpdateTime;                                        // 0x015C(0x0004) 
	unsigned char                                      bAutoDestroyWhenFinished : 1;                             // 0x0160(0x0001) 
	unsigned char                                      bCanBeDamaged : 1;                                        // 0x0160(0x0001) 
	unsigned char                                      bActorIsBeingDestroyed : 1;                               // 0x0160(0x0001) 
	unsigned char                                      bCollideWhenPlacing : 1;                                  // 0x0160(0x0001)
	unsigned char                                      bFindCameraComponentWhenViewTarget : 1;                   // 0x0160(0x0001) 
	unsigned char                                      bRelevantForNetworkReplays : 1;                           // 0x0160(0x0001)
	unsigned char                                      bGenerateOverlapEventsDuringLevelStreaming : 1;           // 0x0160(0x0001) 
	TEnumAsByte<ESpawnActorCollisionHandlingMethod>    SpawnCollisionHandlingMethod;                             // 0x0161(0x0001) 
	unsigned char                                      UnknownData06[0x6];                                       // 0x0162(0x0006) 
	class APawn*                                       Instigator;                                               // 0x0168(0x0008) 
	TArray<class AActor*>                              Children;                                                 // 0x0170(0x0010) 
	class USceneComponent*                             RootComponent;                                            // 0x0180(0x0008) 
	TArray<class AMatineeActor*>                       ControllingMatineeActors;                                 // 0x0188(0x0010) 
	float                                              InitialLifeSpan;                                          // 0x0198(0x0004) 
	unsigned char                                      UnknownData07[0xC];                                       // 0x019C(0x000C) 
	TArray<struct FName>                               Layers;                                                   // 0x01A8(0x0010) 
	unsigned char                                      ParentComponentActor[0x8];                                // 0x01B8(0x0008) TWeakObjectPtr<class AActor>
	unsigned char                                      ParentComponent[0x8];                                     // 0x01C0(0x0008) TWeakObjectPtr<class UChildActorComponent> 
	unsigned char                                      bAllowReceiveTickEventOnDedicatedServer : 1;              // 0x01C8(0x0001)
	unsigned char                                      bActorSeamlessTraveled : 1;                               // 0x01C8(0x0001)
	unsigned char                                      bIgnoresOriginShifting : 1;                               // 0x01C8(0x0001) 
	unsigned char                                      bEnableAutoLODGeneration : 1;                             // 0x01C8(0x0001) 
	unsigned char                                      UnknownData08[0x7];                                       // 0x01C9(0x0007) 
	TArray<struct FName>                               Tags;                                                     // 0x01D0(0x0010) 
	uint64_t                                           HiddenEditorViews;                                        // 0x01E0(0x0008) 
	struct FScriptMulticastDelegate                    OnTakeAnyDamage;                                          // 0x01E8(0x0010) 
	struct FScriptMulticastDelegate                    OnTakePointDamage;                                        // 0x01F8(0x0010) 
	struct FScriptMulticastDelegate                    OnActorBeginOverlap;                                      // 0x0208(0x0010) 
	struct FScriptMulticastDelegate                    OnActorEndOverlap;                                        // 0x0218(0x0010) 
	struct FScriptMulticastDelegate                    OnBeginCursorOver;                                        // 0x0228(0x0010) 
	struct FScriptMulticastDelegate                    OnEndCursorOver;                                          // 0x0238(0x0010) 
	struct FScriptMulticastDelegate                    OnClicked;                                                // 0x0248(0x0010) 
	struct FScriptMulticastDelegate                    OnReleased;                                               // 0x0258(0x0010) 
	struct FScriptMulticastDelegate                    OnInputTouchBegin;                                        // 0x0268(0x0010) 
	struct FScriptMulticastDelegate                    OnInputTouchEnd;                                          // 0x0278(0x0010) 
	struct FScriptMulticastDelegate                    OnInputTouchEnter;                                        // 0x0288(0x0010) 
	struct FScriptMulticastDelegate                    OnInputTouchLeave;                                        // 0x0298(0x0010) 
	struct FScriptMulticastDelegate                    OnActorHit;                                               // 0x02A8(0x0010) 
	struct FScriptMulticastDelegate                    OnDestroyed;                                              // 0x02B8(0x0010) 
	struct FScriptMulticastDelegate                    OnEndPlay;                                                // 0x02C8(0x0010) 
	unsigned char                                      UnknownData09[0xA0];                                      // 0x02D8(0x00A0) 
	TArray<class UActorComponent*>                     BlueprintCreatedComponents;                               // 0x0378(0x0010) 
	TArray<class UActorComponent*>                     InstanceComponents;                                       // 0x0388(0x0010) 
	unsigned char                                      UnknownData10[0x8];                                       // 0x0398(0x0008) MISSED OFFSET

public:
	inline bool IsPlayer(std::string &name) {
		if (name == "PlayerFemale_A" || name == "PlayerFemale_A_C" || name == "PlayerMale_A" || name == "PlayerMale_A_C")
			return true;

		return false;
	}

	inline bool IsVehicle()
	{
		switch (Id)
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