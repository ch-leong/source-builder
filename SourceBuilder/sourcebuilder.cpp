#include "precompiled.h"
#include <windows.h>
#include <locale>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <sstream>

#include "sourcebuilder.h"
#include "class.h"

std::vector<std::string> directories;

bool BuildSources()
{
    for (auto const& directory : directories)
    {
        AnalyzeDirectory(directory);
    }
    return true;
}

bool AnalyzeDirectory(std::string const& directory)
{
    std::vector<std::string> folders;
    std::vector<std::string> files;
    GetFoldersAndFiles(directory, folders, files);

    for (auto const& file : files)
    {
        std::size_t found = file.find(".mold");
        if (found == std::string::npos)
        {
            continue;
        }
        BuildSource(directory + "\\", file);
    }

    for (auto const& folder : folders)
    {
        AnalyzeDirectory(directory + "\\" + folder);
    }

    return true;
}

bool GetFoldersAndFiles(std::string const& directory, std::vector<std::string>& folders, std::vector<std::string>& files)
{
    // Converting char to wchar.
    std::wstring pattern{ directory.begin(), directory.end() };
    pattern.append(L"\\*");

    // Open.
    WIN32_FIND_DATA data{};
    HANDLE hFind = FindFirstFileW(pattern.c_str(), &data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wstringToString;

    do
    {
        // Convering wchar to char.
        std::wstring wTmp{ data.cFileName };
        std::string tmp(wstringToString.to_bytes(wTmp));
        // Preventing taking in current directory and the parent directory.
        if (tmp != "." && tmp != "..")
        {
            size_t dotPos = tmp.find_last_of(".");
            if (dotPos == std::string::npos)
            {
                folders.push_back(tmp);
            }
            else
            {
                files.push_back(tmp);
            }
        }
    } while (FindNextFile(hFind, &data) != 0);

    // Close.
    FindClose(hFind);

    return true;
}

std::vector<std::string> LineToWords(std::string const& line)
{
    std::vector<std::string> words;
    std::string word;
    for (auto const& character : line)
    {
        if (character != ' ' && character != '\n' && character != ':' && character != ',')
        {
            word += character;
        }
        else if (character == ' ' || character == '\n')
        {
            if (word.size() > 0)
            {
                words.push_back(word);
            }
            word.clear();
        }
        else if (character == ':' || character == ',')
        {
            if (word.size() > 0)
            {
                words.push_back(word);
            }
            if (character == ':')
            {
                words.push_back(":");
            }
            word.clear();
        }
    }
    if (word.size() > 0)
    {
        words.push_back(word);
    }
    return std::move(words);
}

bool BuildSource(std::string const& directory, std::string const& file)
{
    std::ifstream moldFile(directory + file);
    if (!moldFile.is_open())
    {
        return false;
    }
    std::string line;
    std::string cppSource, cppHeader;
    Class tmpClass;
    Function tmpFunction;
    bool inClass = false;

    while (getline(moldFile, line))
    {
        std::vector<std::string> words = LineToWords(line);

        // Is a class.
        if (line.find("class") != std::string::npos)
        {
            tmpClass.m_Name = words[1];
            if (words.size() > 2 && words[2] == ":")
            {
                for (unsigned i = 4; i < words.size(); ++i)
                {
                    if (words[i] != "public" && words[i] != "protected")
                    {
                        if (words[i - 1] == "public") tmpClass.m_PublicBaseClasses.push_back(words[i]);
                        else if (words[i - 1] == "protected") tmpClass.m_ProtectedBaseClasses.push_back(words[i]);
                        else tmpClass.m_PrivateBaseClasses.push_back(words[i]);
                    }
                }
            }
            inClass = true;
        }
        else if (inClass)
        {
            // Is a class member function.
            if (line.find(")") != std::string::npos)
            {
                Function memberFunction;
                memberFunction.m_ReturnType = words[0];
                memberFunction.m_Name = words[1];
            }
            // Is a class member variable.
            else
            {

            }
            // End of a class.
            if (words[0][0] == '}')
            {
                tmpClass.ToFile(cppHeader, cppSource);
                inClass = false;
            }
        }
    }


    if (cppHeader.size() > 0)
    {
        std::ofstream cppHeaderFile(directory + file.substr(0, file.find(".mold")) + ".h");
        cppHeaderFile << cppHeader;
        cppHeaderFile.close();
    }

    if (cppSource.size() > 0)
    {
        std::ofstream cppSourceFile(directory + file.substr(0, file.find(".mold")) + ".cpp");
        cppSourceFile << cppSource;
        cppSourceFile.close();
    }

    return true;
}
