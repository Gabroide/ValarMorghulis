#ifndef __ModuleLibrary_h__
#define __ModuleLibrary_h__

#include <map>
#include <vector>
#include <string>

#include "Module.h"

class ModuleLibrary : public Module
{
	public:
		ModuleLibrary();
		~ModuleLibrary();

		bool					Init()		override;
		bool					CleanUp()	override;

		update_status			Update()	override;

		void					UpdateMeshesList();
		void					UpdateTexturesList();
		void					UpdateScenesList();

	public:
		bool					 toBeDeleted = false;
		bool			  		 removeHead = false;
	
	public:
		std::vector<std::string>* fileMeshesList = nullptr;
		std::vector<std::string>* fileTexturesList	= nullptr;
		std::vector<std::string>* fileScenesList	= nullptr;

};

#endif // __ModuleLibrary_h__
