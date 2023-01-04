#pragma once

#include <memory>

namespace ConsoleGame
{
   class GameEventAggregator;
   class IGameClock;
   class IGameInputHandler;
   class IGameRenderer;
   class IGame;
   class IThread;

   class GameRunner
   {
   public:
      GameRunner( const std::shared_ptr<GameEventAggregator> eventAggregator,
                  const std::shared_ptr<IGameClock> clock,
                  const std::shared_ptr<IGameInputHandler> inputHandler,
                  const std::shared_ptr<IGameRenderer> renderer,
                  const std::shared_ptr<IGame> game,
                  const std::shared_ptr<IThread> thread );

      virtual void Run();

   private:
      void HandleShutdownEvent();

   private:
      const std::shared_ptr<IGameClock> _clock;
      const std::shared_ptr<IGameInputHandler> _inputHandler;
      const std::shared_ptr<IGameRenderer> _renderer;
      const std::shared_ptr<IGame> _game;

      bool _isRunning;
   };
}
