#include "Timer.h"

#include <chrono>

CommonUtilities::Timer::Timer(float aFixedTickTime) : myFixedTickTime(aFixedTickTime)
{
}

void CommonUtilities::Timer::Start()
{
    myStartTime = std::chrono::high_resolution_clock::now();
    myLastTime = myStartTime;
    myTotalTime = 0;
}

void CommonUtilities::Timer::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - myLastTime;
    std::chrono::duration<double> total = currentTime - myStartTime;
    myLastTime = currentTime;
    
    myDeltaTime = delta.count();
    myTotalTime = total.count();

    myAccumulatedTime += myDeltaTime;
    myFixedRateDelta = 0;

    while (myAccumulatedTime >= myFixedTickTime)
    {
        myAccumulatedTime -= myFixedTickTime;
        ++myFixedRateDelta;
        ++myFixedRate;
    }
    
    
}
