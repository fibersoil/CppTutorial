#include "NewCppTutorialEditor.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FNewCppTutorialEditorModule, NewCppTutorialEditor);

void FNewCppTutorialEditorModule::StartupModule()
{
	// Check if Editor is valid
	if (GUnrealEd)
	{
		TSharedPtr<FMoveComponentVisualizer> MoveVisualizer = MakeShareable(new FMoveComponentVisualizer);
		if (MoveVisualizer.IsValid())
		{
			GUnrealEd->RegisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName(), MoveVisualizer);
			MoveVisualizer->OnRegister();
		}
	}
} 

void FNewCppTutorialEditorModule::ShutdownModule()
{
	// Check if Editor is valid
	if (GUnrealEd) {
		GUnrealEd->UnregisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName());
	}
}