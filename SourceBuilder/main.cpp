/******************************************************************************/
/**
* \file main.cpp
* \author Leong Chee Hwa, cheehwa1994\@hotmail.com
* \brief Program entry point.
*/
/******************************************************************************/
#include "precompiled.h"
#include "sourcebuilder.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return -1;
    }

    for (unsigned i = 1; i < argc; ++i)
    {
        directories.push_back(argv[i]);
    }

    if (!BuildSources())
    {
        return -1;
    }

    return 0;
}
