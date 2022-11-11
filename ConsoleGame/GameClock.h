#pragma once

#include <memory>
#include <chrono>

#include "IGameClock.h"

namespace ConsoleGame
{
   class IHighResolutionClock;
   class ISleeper;

   class GameClock : public IGameClock
   {
   public:
      GameClock( const std::shared_ptr<IHighResolutionClock> highResolutionClock,
                 const std::shared_ptr<ISleeper> sleeper,
                 int framesPerSecond );

      void Start() override;
      void Tick() override;
      void Stop() override;

      int GetFramesPerSecond() const override { return _framesPerSecond; }
      long long GetTotalFrameCount() const override { return _totalFrameCount; }
      long long GetLagFrameCount() const override { return _lagFrameCount; }

   private:
      const std::shared_ptr<IHighResolutionClock> _highResolutionClock;
      const std::shared_ptr<ISleeper> _sleeper;

      int _framesPerSecond;
      long long _totalFrameCount;
      long long _lagFrameCount;
      std::chrono::steady_clock::time_point _frameStartTimeNano;
      long long _nanoSecondsPerFrame;
      bool _isRunning;
   };
}
