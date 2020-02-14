#pragma once
#include <string>
#include <vector>
#include "variable.h"

class Function
{
public:
    Function();
    bool m_Inline;
    std::string m_ReturnType;
    std::string m_Name;
    std::vector<Variable> m_Paramters;
};
