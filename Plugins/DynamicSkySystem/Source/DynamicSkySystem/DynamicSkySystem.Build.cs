using UnrealBuildTool;
 
public class DynamicSkySystem : ModuleRules
{
	public DynamicSkySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Engine" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}