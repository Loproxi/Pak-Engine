#include "WinAssets.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ImGuiUtils.h"

WinAssets::WinAssets()
{
	name = "Assets";
	app = Application::GetInstance();
}

WinAssets::~WinAssets()
{
	RELEASE(rootnodeassets);
}

void WinAssets::Start()
{
	rootnodeassets = new AssetsDirectory("Assets", "Assets");

	app->fileSystem->RecursiveAddUpdateAssetFiles(*rootnodeassets);

}

void WinAssets::Draw()
{
	if (isEnabled)
	{
		if (ImGui::Begin(name.c_str(), &isEnabled))
		{

			DrawRecursivelyAssetTree(*rootnodeassets);
			
		}
		ImGui::End();
	}
}

void WinAssets::DrawRecursivelyAssetTree(AssetsDirectory& dir)
{

	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

	if (dir.directorydirs.size() == 0 && dir.directoryfiles.size() == 0)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}
	/*else if (dir.directoryfiles.size() >= 0 && )
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf;
	}*/

	if (selectednode == &dir)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	}

	bool nodeOpen = ImGui::TreeNodeEx(dir.dirname.c_str(), nodeFlags);
	//if (dir.directorydirs.size() == 0)nodeOpen = false;

	if (ImGui::IsItemClicked(0))
	{
		selectednode = &dir;
	}

	
	
	if (nodeOpen)
	{
		DrawAssetFile(dir);

		for (int i = 0; i < dir.directorydirs.size(); i++)
		{
			DrawRecursivelyAssetTree(dir.directorydirs[i]);
		}

		if (dir.directorydirs.size() != 0 || dir.directoryfiles.size() != 0)
		{
			ImGui::TreePop();
		}
		
	}
	
}

void WinAssets::DrawAssetFile(AssetsDirectory& dir)
{
	
	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

	nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	bool nodeOpen = false;

	for (int i = 0; i < dir.directoryfiles.size(); i++)
	{
		
		nodeOpen = ImGui::TreeNodeEx(dir.directoryfiles[i].filename.c_str(), nodeFlags);
	}
	

}