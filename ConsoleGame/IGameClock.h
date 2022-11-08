#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IGameClock
   {
   public:
      virtual void Start() = 0;
      virtual void Tick() = 0;
      virtual void Stop() = 0;

      virtual int GetFramesPerSecond() const = 0;
      virtual long long GetTotalFrameCount() const = 0;
      virtual long long GetLagFrameCount() const = 0;
   };
}
