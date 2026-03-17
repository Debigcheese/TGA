#pragma once

class MapConfigSingleton
{
public:
    int NumPathsToCarve;
    int PathStepsPerCarve;
    int InitialAreaSize;

    static MapConfigSingleton* GetInstance();

private:
    MapConfigSingleton();
    static MapConfigSingleton* myInstance;
};
