#pragma once
#include <string>
#include <vector>
#include "function.h"

class Class
{
public:
    Class(std::string const& name = "");
    void ToFile(std::string& header, std::string& source);
    void Clear();
    std::string m_Name;
    std::vector<Class> m_PublicBaseClasses;
    std::vector<Class> m_ProtectedBaseClasses;
    std::vector<Class> m_PrivateBaseClasses;
    std::vector<Function> m_Constructors;
    std::vector<Function> m_PublicMemberFunctions;
    std::vector<Function> m_ProtectedMemberFunctions;
    std::vector<Function> m_PrivateMemberFunctions;
    std::vector<Function> m_StaticMemberFunctions;
};
