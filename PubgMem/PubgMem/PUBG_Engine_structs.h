#pragma once

//Vector3
class Vector3D
{
public:
	Vector3D() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3D()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3D v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3D v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3D operator+(Vector3D v)
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator-(Vector3D v)
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
};
// Enum Engine.ENetRole
enum class ENetRole
{
	ROLE_None = 0,
	ROLE_SimulatedProxy = 1,
	ROLE_AutonomousProxy = 2,
	ROLE_Authority = 3,
	ROLE_MAX = 4
};

// Enum Engine.TextureAddress
enum class ETextureAddress
{
	TA_Wrap = 0,
	TA_Clamp = 1,
	TA_Mirror = 2,
	TA_MAX = 3
};


// Enum Engine.ESpawnActorCollisionHandlingMethod
enum class ESpawnActorCollisionHandlingMethod
{
	ESpawnActorCollisionHandlingMethod__Undefined = 0,
	ESpawnActorCollisionHandlingMethod__AlwaysSpawn = 1,
	ESpawnActorCollisionHandlingMethod__AdjustIfPossibleButAlwaysSpawn = 2,
	ESpawnActorCollisionHandlingMethod__AdjustIfPossibleButDontSpawnIfColliding = 3,
	ESpawnActorCollisionHandlingMethod__DontSpawnIfColliding = 4,
	ESpawnActorCollisionHandlingMethod__ESpawnActorCollisionHandlingMethod_MAX = 5
};

// Enum Engine.EAutoReceiveInput
enum class EAutoReceiveInput
{
	EAutoReceiveInput__Disabled = 0,
	EAutoReceiveInput__Player0 = 1,
	EAutoReceiveInput__Player1 = 2,
	EAutoReceiveInput__Player2 = 3,
	EAutoReceiveInput__Player3 = 4,
	EAutoReceiveInput__Player4 = 5,
	EAutoReceiveInput__Player5 = 6,
	EAutoReceiveInput__Player6 = 7,
	EAutoReceiveInput__Player7 = 8,
	EAutoReceiveInput__EAutoReceiveInput_MAX = 9
};

// Enum Engine.EInputConsumeOptions
enum class EInputConsumeOptions
{
	ICO_ConsumeAll = 0,
	ICO_ConsumeBoundKeys = 1,
	ICO_ConsumeNone = 2,
	ICO_MAX = 3
};


// ScriptStruct Engine.ActorTickFunction
// 0x0008 (0x0058 - 0x0050)
struct FActorTickFunction
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0050(0x0008) MISSED OFFSET
};

struct FScriptMulticastDelegate
{
	char UnknownData[16];
};

