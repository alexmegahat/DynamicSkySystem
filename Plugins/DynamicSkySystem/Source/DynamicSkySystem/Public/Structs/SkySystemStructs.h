#pragma once

#include "CoreMinimal.h"
#include "SkySystemStructs.generated.h"

USTRUCT(BlueprintType)
struct FDirectionalLightSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DirLightIntensity{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DirLightColor{1.f,1.f,1.f,1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DirLightSourceAngle{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Temperature{0.f};
};

USTRUCT(BlueprintType)
struct FSkyLightSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkyLightIntensityScale{0.f};
};

USTRUCT(BlueprintType)
struct FSkyAtmosphereSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MultiScattering{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RayleighScatteringScale{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor RayleighScattering{1.f,1.f,1.f,1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MieScatteringScale{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MieAbsorptionScale{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MieAnisotropy{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AerialPerspectiveViewDistanceScale{0.f};
};

USTRUCT(BlueprintType)
struct FExponentialHeightFogSettings
{
	GENERATED_BODY()

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EmissiveColor{1.f,1.f,1.f,1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtinctionScale{0.f};
};


