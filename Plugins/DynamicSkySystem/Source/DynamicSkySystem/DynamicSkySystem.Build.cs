using UnrealBuildTool;
 
public class DynamicSkySystem : ModuleRules
{
	public DynamicSkySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Niagara" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}