#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGameClock
   {
   public:
      virtual void StartFrame() = 0;
      virtual void WaitForNextFrame() = 0;

      virtual int GetFramesPerSecond() const = 0;
      virtual long long GetTotalFrameCount() const = 0;
      virtual long long GetLagFrameCount() const = 0;
   };
}
