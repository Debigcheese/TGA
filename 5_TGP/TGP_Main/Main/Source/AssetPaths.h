#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class AssetPaths
{
public:
	static void Init();

	static fs::path Resolve(const fs::path& aRelativePath);
	static std::string ResolveString(const std::string& aRelativePath);
	static std::wstring ResolveWString(const std::wstring& aRelativePath);

	static const fs::path& GetExeDirectory();
	static fs::path Find(const std::string& aFileName);

private:
	static void BuildIndex(const fs::path& anAssetsFolder);

	static inline std::unordered_map<std::string, fs::path> myFileIndex;
	static inline fs::path myExeDirectory;
	static inline std::vector<fs::path> mySearchRoots;
};
