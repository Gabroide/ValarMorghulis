#ifndef __ModuleFileSystem_h__
#define __ModuleFileSystem_h__

#include "Module.h"
#include "Crossguid/crossguid/guid.hpp"
#include <map>
#include <vector>
#include <string>

class ModuleFileSystem : public Module
{
public:
	ModuleFileSystem();
	~ModuleFileSystem();

	bool		Init()		override;
	bool		CleanUp()	override;
	bool		AddPath(const char* path);
	bool		Remove(const char* pathAndFileName);
	bool		Exists(const char* pathAndFileName) const;
	bool		MakeDirectory(const char* path);
	bool		IsDirectory(const char* pathAndFileName) const;
	bool		Copy(const char* sourcePath, const char* destinationPath);

	unsigned	Load(const char* pathAndFileName, char** buffer) const;
	unsigned	Save(const char* pathAndFileName, const void* buffer, unsigned size, bool append = false) const;
	
	void		GetFilesFromDirectory(const char* directory, std::vector<std::string>& fileList) const;
	void		ChangePathSlashes(std::string& fullPath) const;
	void		SplitFilePath(const char* fullPath, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;

	std::map<std::string, std::string> GetFilesFromDirectoryRecursive(const char* directory);
	
	std::string NewGuuid();

public:
	char*		basePath = nullptr;

};

#endif // __ModuleFileSystem_h__
