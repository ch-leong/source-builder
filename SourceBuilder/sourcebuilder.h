#pragma once
#include <string>
#include <vector>

extern std::vector<std::string> directories;

bool BuildSources();
bool AnalyzeDirectory(std::string const& directory);
bool GetFoldersAndFiles(std::string const& directory, std::vector<std::string>& folders, std::vector<std::string>& files);
bool BuildSource(std::string const& directory, std::string const& file);
