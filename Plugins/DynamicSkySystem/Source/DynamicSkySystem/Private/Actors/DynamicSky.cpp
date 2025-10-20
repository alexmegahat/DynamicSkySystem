// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DynamicSky.h"

#include <Windows.Media.Audio.h>

#include "NiagaraComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"


// Sets default values
ADynamicSky::ADynamicSky()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SkySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphere"));
	SkySphere->SetupAttachment(GetRootComponent());
	SkySphere->SetRelativeScale3D(FVector(100000.0f, 100000.0f, 100000.0f)); //giant sphere!

	SunDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunDirectionalLight"));
	SunDirectionalLight->SetupAttachment(GetRootComponent());
	SunDirectionalLight->SetUseTemperature(true);
	SunDirectionalLight->SetAtmosphereSunLightIndex(0);
	SunDirectionalLight->SetForwardShadingPriority(1);

	MoonDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonDirectionalLight"));
	MoonDirectionalLight->SetupAttachment(GetRootComponent());
	MoonDirectionalLight->SetUseTemperature(true);
	MoonDirectionalLight->SetAtmosphereSunLightIndex(1);
	MoonDirectionalLight->SetForwardShadingPriority(0);

	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricCloud"));
	VolumetricCloud->SetupAttachment(GetRootComponent());

	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->SetupAttachment(GetRootComponent());

	//Override exposure: make it so that it doesn't affect the level
	PostProcess->Settings.bOverride_AutoExposureMinBrightness = true;
	PostProcess->Settings.bOverride_AutoExposureMaxBrightness = true;
	PostProcess->Settings.AutoExposureMinBrightness = 0.5f;
	PostProcess->Settings.AutoExposureMaxBrightness = 0.5f;
	//make post process infinite
	PostProcess->bUnbound = true;

	SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
	SkyAtmosphere->SetupAttachment(GetRootComponent());

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(GetRootComponent());
	SkyLight->SetRealTimeCapture(true);
	

	ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
	ExponentialHeightFog->SetupAttachment(GetRootComponent());
	ExponentialHeightFog->bEnableVolumetricFog = true;

	NiagaraWeatherEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraWeatherEffects"));
	NiagaraWeatherEffect->SetupAttachment(GetRootComponent());
	
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicSky::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ChangeDirectionalLightCastVolumetricShadow(bShouldVolumetricCloudsCastShadow);
}

// Called when the game starts or when spawned
void ADynamicSky::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamicSky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADynamicSky::ChangeDirectionalLightCastVolumetricShadow(const bool bInShouldCastVolumetricShadow) const
{
	SunDirectionalLight->bCastCloudShadows = bInShouldCastVolumetricShadow;
	MoonDirectionalLight->bCastCloudShadows = bInShouldCastVolumetricShadow;
}

