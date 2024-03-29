#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IFrameRateProvider
   {
   public:
      virtual long long GetCurrentFrame() const = 0;
      virtual float GetFrameSeconds() const = 0;
      virtual long long GetElapsedNanoseconds() const = 0;
      virtual long long GetAverageFrameRate() const = 0;
   };
}
