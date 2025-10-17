#pragma once

UENUM(BlueprintType)
enum class EDirectionalLightsVisualisationType : uint8
{
	CustomBillboard UMETA(DisplayName = "Custom Billboard"),
	DirectionalLightLuminanceOutput UMETA(DisplayName = "Directional Light Luminance Output"),
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ECloudsVisualisationType : uint8
{
	TwoDimensionalClouds UMETA(DisplayName = "2D Clouds"),
	VolumetricClouds UMETA(DisplayName = "Volumetric Clouds"),
	None UMETA(DisplayName = "None")
};