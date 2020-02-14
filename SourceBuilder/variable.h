#pragma once
#include <string>

class Variable
{
public:
    Variable(std::string const& type, std::string const& name);
    std::string m_Type;
    std::string m_Name;
};
