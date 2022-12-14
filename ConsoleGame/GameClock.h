#pragma once

#include <memory>

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

      void StartFrame() override;
      void WaitForNextFrame() override;

      int GetFramesPerSecond() const override { return _framesPerSecond; }
      long long GetTotalFrameCount() const override { return _totalFrameCount; }
      long long GetLagFrameCount() const override { return _lagFrameCount; }

   private:
      const std::shared_ptr<IHighResolutionClock> _highResolutionClock;
      const std::shared_ptr<ISleeper> _sleeper;

      int _framesPerSecond;
      long long _totalFrameCount;
      long long _lagFrameCount;
      long long _frameStartTimeNano;
      long long _nanoSecondsPerFrame;
   };
}
