#pragma once
#include <chrono>
#include <cstdint>

namespace CommonUtilities
{
    class Timer
    {
    public:
        Timer(float aFixedTickTime = 1.f/60.f);
        Timer(const Timer &aTimer) = delete;
        Timer& operator=(const Timer &aTimer) = delete;
        void Start();
        void Update();
        float GetDeltaTime() const { return myDeltaTime;}
        double GetTotalTime() const { return myTotalTime;}
        int GetFixedRateTickDeltaCount() const { return myFixedRateDelta;}
        uint64_t GetFixedRateTickCount() const { return myFixedRate;}
        
    private:
        std::chrono::high_resolution_clock::time_point myStartTime;
        std::chrono::high_resolution_clock::time_point myLastTime;
        float myFixedTickTime;
        float myDeltaTime;
        float myAccumulatedTime;
        double myTotalTime = 0;
        int myFixedRateDelta;
        uint64_t myFixedRate;
       };

}

