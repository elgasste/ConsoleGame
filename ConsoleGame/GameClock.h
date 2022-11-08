#pragma once

#include <chrono>

#include "IGameClock.h"

namespace ConsoleGame
{
   class GameClock : public IGameClock
   {
   public:
      GameClock( int framesPerSecond );

      void Start() override;
      void Tick() override;
      void Stop() override;

      int GetFramesPerSecond() const override { return _framesPerSecond; }
      long long GetTotalFrameCount() const override { return _totalFrameCount; }
      long long GetLagFrameCount() const override { return _lagFrameCount; }

   private:
      int _framesPerSecond;
      long long _totalFrameCount;
      long long _lagFrameCount;
      std::chrono::steady_clock::time_point _frameStartTimeNano;
      long long _nanoSecondsPerFrame;
      bool _isRunning;
   };
}
