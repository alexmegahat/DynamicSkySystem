// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VolumetricCloudComponent.h"
#include "GameFramework/Actor.h"
#include "Enums/SkySystemEnumTypes.h"
#include "DynamicSky.generated.h"



//////////////////////////////////////////////////////////////////////////////////////////
// ==============
// MACROS
// ==============
//{///////////////////////////////////////////////////////////////////////////////////////

#define PROPERTY_ACCESSOR(Type, PropertyName) \
	FORCEINLINE void Set##PropertyName(Type In##PropertyName) { PropertyName = In##PropertyName; } \
	FORCEINLINE void Get##PropertyName() const { return PropertyName; }

//-------------------------------------------------------
//} END MACROS


////////////////////////////
// Forward Declarations
class UPostProcessComponent;
class USkyAtmosphereComponent;
class UExponentialHeightFogComponent;

//--------------------------------------------------
// DynamicSkySystem Actor class
//
// Used as a base c++ class for dynamic sky actor.
// See BP child class that you can place into the world.
//--------------------------------------------------
UCLASS()
class DYNAMICSKYSYSTEM_API ADynamicSky : public AActor
{
	GENERATED_BODY()

public:
	ADynamicSky();

////////////////////////////
// Functions
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ChangeDirectionalLightCastVolumetricShadow(const bool bInShouldCastVolumetricShadow) const;

////////////////////////////
// Properties
protected:
	//--------------------------------------------------
	// NOT exposed to BP
	//--------------------------------------------------
	
	//Something
	
	

	//--------------------------------------------------
	// Exposed to BP
	//--------------------------------------------------

	////////////////////////////
	// Components
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* SkySphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDirectionalLightComponent* SunDirectionalLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDirectionalLightComponent* MoonDirectionalLight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UVolumetricCloudComponent* VolumetricCloud;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPostProcessComponent* PostProcess;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkyLightComponent* SkyLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UExponentialHeightFogComponent* ExponentialHeightFog;

	////////////////////////////
	// Runtime
	
	UPROPERTY(BlueprintReadWrite)
	float RunningSeconds = 0.f;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* Created_DynMI_SkySphere;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* Created_DynMI_VolumetricCloud;

	
	////////////////////////////
	// 01 - Basic Settings
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings"), DisplayName = "Directional Lights Visualisation Type")
	EDirectionalLightsVisualisationType DirectionalLightsVisualisationType = EDirectionalLightsVisualisationType::CustomBillboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings", ClampMin = 0.f, ClampMax = 360.f))
	float DirectionalLightsXYRotation = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings", ClampMin = 0.f))
	float TimeMultiplier = 1.f;
	
	//Current time of the day, constantly updates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings", ClampMin = 0.f, ClampMax = 24.f))
	float TimeOfDay = 12.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings", ClampMin = 5.f, ClampMax = 8.f))
	float DawnTime = 7.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "01 - Basic Settings", ClampMin = 18.f, ClampMax = 20.f))
	float DuskTime = 19.f;
	
	////////////////////////////
	// 02 - Day Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings", ClampMin = 0.f))
	float SunLightIntensity = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings"))
	FLinearColor SunLightColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings"))
	FLinearColor DayTimeRayleighScattering = FLinearColor(0.175f, 0.41f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings"))
	float DayTimeMultiScattering = 1.f;

	//-----------------
	//Sun Directional Light Luminance Output
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::DirectionalLightLuminanceOutput", EditConditionHides = "true"))
	float SunLightSourceAngle = 1.f;

	//-----------------

	//-----------------
	//Sun Billboard
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float SunBillboardScale = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float SunBillboardBrightness = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "02 - Day Settings", ClampMin = 0.f, ClampMax = 360.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float SunBillboardRotation = 1.f;
	//-----------------
	
	////////////////////////////
	// 03 - Night Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", ClampMin = 0.f))
	float MoonLightIntensity = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings"))
	FLinearColor MoonLightColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings"))
	float MoonLightTemperature = 9000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings"))
	FLinearColor NightTimeRayleighScattering = FLinearColor(0.175f, 0.41f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings"))
	float NightTimeMultiScattering = 1.f;

	//-----------------
	///Moon Directional Light Luminance Output
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::DirectionalLightLuminanceOutput", EditConditionHides = "true"))
	float MoonLightSourceAngle = 1.f;
	//-----------------
	
	//-----------------
	//Moon Billboard
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float MoonBillboardScale = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", ClampMin = 0.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float MoonBillboardBrightness = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", ClampMin = 0.f, ClampMax = 360.f, EditCondition = "DirectionalLightsVisualisationType == EDirectionalLightsVisualisationType::CustomBillboard", EditConditionHides = "true"))
	float MoonBillboardRotation = 1.f;
	//-----------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings"))
	bool bShouldShowNightStars = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "03 - Night Settings", EditCondition = bShouldShowNightStars))
	UMaterialInstance* NightSkyMaterial;
	
	////////////////////////////
	// 04 - Cloud Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings"))
	ECloudsVisualisationType CloudsVisualisationType = ECloudsVisualisationType::VolumetricClouds;

	//-----------------
	//2D Clouds
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D Clouds Texture")
	UTexture2D* TwoDimensionalCloudsTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D Clouds Panning Speed")
	float TwoDimensionalCloudsPanningSpeed = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D Clouds Tiling")
	float TwoDimensionalCloudsTiling = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D Clouds Brightness")
	float TwoDimensionalCloudsBrightness = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D DayTime Atmosphere Tint Strength")
	float TwoDimensionalCloudsDayTimeAtmosphereTintStrength = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::TwoDimensionalClouds", EditConditionHides = "true"), DisplayName = "2D NightTime Atmosphere Tint Strength")
	float TwoDimensionalCloudsNightTimeAtmosphereTintStrength = 1.f;
	//-----------------

	//-----------------
	//Volumetric Clouds
	//-----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds Material")
	UMaterialInstance* VolumetricCloudsMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Should Volumetric Clouds Cast Shadow")
	bool bShouldVolumetricCloudsCastShadow = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds Panning Speed")
	float VolumetricCloudsPanningSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = -1.f, ClampMax = 1.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds Panning DirX")
	float VolumetricCloudsPanningDirX = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = -1.f, ClampMax = 1.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds Panning DirY")
	float VolumetricCloudsPanningDirY = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.f, ClampMax = 20.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds LayerBottom Altitude")
	float VolumetricCloudsLayerBottomAltitude = 7.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "04 - Cloud Settings", ClampMin = 0.1f, ClampMax = 20.f, EditCondition = "CloudsVisualisationType == ECloudsVisualisationType::VolumetricClouds", EditConditionHides = "true"), DisplayName = "Volumetric Clouds Layer Height")
	float VolumetricCloudsLayerHeight = 8.f;

	//-----------------
};
