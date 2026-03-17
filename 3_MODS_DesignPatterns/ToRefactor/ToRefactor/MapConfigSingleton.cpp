#include "MapConfigSingleton.h"


MapConfigSingleton* MapConfigSingleton::myInstance = nullptr;

MapConfigSingleton* MapConfigSingleton::GetInstance()
{
    if (!myInstance)
    {
        myInstance = new MapConfigSingleton();
    }
    return myInstance;
}

MapConfigSingleton::MapConfigSingleton()
{
    NumPathsToCarve = 5;
    PathStepsPerCarve = 300;
    InitialAreaSize = 5;
}