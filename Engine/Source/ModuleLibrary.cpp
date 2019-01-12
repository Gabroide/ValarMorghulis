#include <thread>

#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleLibrary.h"
#include "MaterialImporter.h"
#include "MeshImporter.h"

#include "IMGUI\imgui.h"

bool stopWatcher = false;

// Constructor
ModuleLibrary::ModuleLibrary() 
{
	
}

// Destructor
ModuleLibrary::~ModuleLibrary() 
{

}

void LibraryWatcher() 
{
	return;
	std::map<std::string, std::string> oldFilesAssets;
	std::map<std::string, std::string> currentFilesAssets;
	std::map<std::string, std::string> currentFilesLibrary;
	
	while (!stopWatcher) 
	{
		currentFilesAssets = App->fileSystem->GetFilesFromDirectoryRecursive("/Assets/", true);
		
		if ((oldFilesAssets.size() == 0 && oldFilesAssets.size() != currentFilesAssets.size()) || oldFilesAssets.size() < currentFilesAssets.size()) 
		{
			currentFilesLibrary = App->fileSystem->GetFilesFromDirectoryRecursive("/Library/", false);
			
			for (std::map<std::string, std::string>::iterator iterator = currentFilesAssets.begin(); iterator != currentFilesAssets.end(); ++iterator) 
			{
				std::string fileName = (*iterator).first;
				App->fileSystem->ChangePathSlashes(fileName);
				
				if (currentFilesLibrary.find(fileName.substr(0, fileName.length() - 4)) == currentFilesLibrary.end()) 
				{
					std::string ext(fileName.substr(fileName.length() - 3));

					std::string fullPath = (*iterator).second;
					fullPath.append(fileName);
					
					if (ext == "png" || ext == "tif") 
					{
						MaterialImporter::Import(fullPath.c_str());
					}
					
					if (ext == "fbx" || ext == "FBX") 
					{
						MeshImporter::ImportFBX(fullPath.c_str());
					}
				}
			}
		
			oldFilesAssets = currentFilesAssets;
			App->library->UpdateMeshesList();
			App->library->UpdateTexturesList();
		}
		else if (oldFilesAssets.size() > currentFilesAssets.size()) 
		{
			oldFilesAssets = currentFilesAssets;
		}
	}

	Sleep(1000);
}

bool ModuleLibrary::Init() 
{
	std::thread watcherThread(LibraryWatcher);

	watcherThread.detach();

	UpdateMeshesList();
	UpdateTexturesList();

	return true;
}

update_status ModuleLibrary::Update() 
{
	if (toBeDeleted) {
		toBeDeleted = false;
		
		if (removeHead) 
		{
			UpdateMeshesList();
		}
		else 
		{
			UpdateTexturesList();
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleLibrary::CleanUp() 
{
	stopWatcher = true;

	return true;
}

void ModuleLibrary::UpdateMeshesList() 
{
	fileMeshesList.clear();
	App->fileSystem->GetFilesFromDirectory("/Library/Meshes/", fileMeshesList);
}

void ModuleLibrary::UpdateTexturesList() 
{
	fileTexturesList.clear();
	App->fileSystem->GetFilesFromDirectory("/Library/Textures/", fileTexturesList);
}