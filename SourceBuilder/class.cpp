#include "precompiled.h"
#include "class.h"

Class::Class(std::string const& name)
    : m_Name(name)
    , m_PublicBaseClasses()
    , m_ProtectedBaseClasses()
    , m_PrivateBaseClasses()
    , m_Constructors()
    , m_PublicMemberFunctions()
    , m_ProtectedMemberFunctions()
    , m_PrivateMemberFunctions()
    , m_StaticMemberFunctions()
{}

void Class::ToFile(std::string& header, std::string& source)
{
    header += "class ";
    header += m_Name;
    if (m_PublicBaseClasses.size() > 0 || m_ProtectedBaseClasses.size() > 0 || m_PrivateBaseClasses.size() > 0)
    {
        header += " : ";
    }
    for (auto const& baseClass : m_PublicBaseClasses)
    {
        if (header.back() != ' ')
        {
            header += ", ";
        }
        header += "public " + baseClass.m_Name;
    }
    for (auto const& baseClass : m_ProtectedBaseClasses)
    {
        if (header.back() != ' ')
        {
            header += ", ";
        }
        header += "protected " + baseClass.m_Name;
    }
    for (auto const& baseClass : m_PrivateBaseClasses)
    {
        if (header.back() != ' ')
        {
            header += ", ";
        }
        header += baseClass.m_Name;
    }
    header += '\n';
    header += '{';
    header += '\n';

    header += "};";
    header += '\n';

    Clear();
}

void Class::Clear()
{
    m_Name.clear();
    m_PublicBaseClasses.clear();
    m_ProtectedBaseClasses.clear();
    m_PrivateBaseClasses.clear();
    m_Constructors.clear();
    m_PublicMemberFunctions.clear();
    m_ProtectedMemberFunctions.clear();
    m_PrivateMemberFunctions.clear();
    m_StaticMemberFunctions.clear();
}
