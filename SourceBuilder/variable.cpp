#include "precompiled.h"
#include "variable.h"

Variable::Variable(std::string const& type, std::string const& name)
    : m_Type(type)
    , m_Name(name)
{}
