#include "AssetPaths.h"
#include <Windows.h>
#include <algorithm>
#include <cctype>

namespace
{
	std::string ToLower(std::string aText)
	{
		std::transform(aText.begin(), aText.end(), aText.begin(),
		               [](unsigned char aChar) { return static_cast<char>(std::tolower(aChar)); });
		return aText;
	}
}

void AssetPaths::Init()
{
	wchar_t buffer[MAX_PATH] = {};
	GetModuleFileNameW(nullptr, buffer, MAX_PATH);
	myExeDirectory = fs::path(buffer).parent_path();

	mySearchRoots.clear();
	fs::path dir = myExeDirectory;
	for (int i = 0; i < 4; ++i)
	{
		mySearchRoots.push_back(dir);
		if (dir == dir.parent_path())
			break;
		dir = dir.parent_path();
	}
	for (const fs::path& root : mySearchRoots)
	{
		std::error_code error;
		if (fs::is_directory(root / "Assets", error))
		{
			BuildIndex(root / "Assets");
			break;
		}
	}
}

fs::path AssetPaths::Resolve(const fs::path& aRelativePath)
{
	if (aRelativePath.is_absolute())
		return aRelativePath;

	if (!aRelativePath.has_parent_path())
	{
		const auto it = myFileIndex.find(ToLower(aRelativePath.string()));
		if (it != myFileIndex.end())
			return it->second;
	}
	for (const fs::path& root : mySearchRoots)
	{
		const fs::path candidate = root / aRelativePath;
		std::error_code error;
		if (fs::exists(candidate, error))
			return candidate.lexically_normal();
	}

	const std::string message = "AssetPaths: could not find '" + aRelativePath.string() + "'\n";
	OutputDebugStringA(message.c_str());
	return myExeDirectory / aRelativePath;
}

std::string AssetPaths::ResolveString(const std::string& aRelativePath)
{
	return Resolve(aRelativePath).string();
}

std::wstring AssetPaths::ResolveWString(const std::wstring& aRelativePath)
{
	return Resolve(aRelativePath).wstring();
}

const fs::path& AssetPaths::GetExeDirectory()
{
	return myExeDirectory;
}

void AssetPaths::BuildIndex(const fs::path& anAssetsFolder)
{
	myFileIndex.clear();

	std::error_code error;
	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(anAssetsFolder, error))
	{
		if (!entry.is_regular_file())
			continue;
		const std::string fileName = ToLower(entry.path().filename().string());
		const auto [it, inserted] = myFileIndex.try_emplace(fileName, entry.path().lexically_normal());
		if (!inserted)
		{
			const std::string message = "AssetPaths: duplicate file name '" + fileName + "', using " + it->second.
				string() + "\n";
			OutputDebugStringA(message.c_str());
		}
	}
}

fs::path AssetPaths::Find(const std::string& aFileName)
{
	const auto it = myFileIndex.find(ToLower(aFileName));
	if (it != myFileIndex.end())
		return it->second;

	const std::string message = "AssetPaths: no asset named '" + aFileName + "'\n";
	OutputDebugStringA(message.c_str());
	return {};
}
