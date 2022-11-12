#pragma once

#include <memory>

#include "IGameRunner.h"

namespace ConsoleGame
{
   class IGameEventAggregator;
   class IGameClock;
   class IGameInputHandler;
   class IGameRenderer;

   class GameRunner : public IGameRunner
   {
   public:
      GameRunner( const std::shared_ptr<IGameEventAggregator> eventAggregator,
                  const std::shared_ptr<IGameClock> clock,
                  const std::shared_ptr<IGameInputHandler> inputHandler,
                  const std::shared_ptr<IGameRenderer> renderer );

      void Run() override;

   private:
      void HandleQuitEvent();

   private:
      const std::shared_ptr<IGameClock> _clock;
      const std::shared_ptr<IGameInputHandler> _inputHandler;
      const std::shared_ptr<IGameRenderer> _renderer;

      bool _isRunning;
   };
}
