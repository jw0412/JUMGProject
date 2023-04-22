using UnrealBuildTool;

public class TestProject : ModuleRules
{
	public TestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] {
                            "Core",
                            "CoreUObject",
                            "Engine",
                            "InputCore",

                            "UMG",
                            "Slate",
                            "SlateCore",
                         });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
