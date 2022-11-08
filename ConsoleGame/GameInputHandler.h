#pragma once

#include <memory>
#include <map>

#include "IGameInputHandler.h"

namespace ConsoleGame
{
   class IGameInputReader;
   class IGameStateProvider;
   class IGameEventAggregator;
   enum class GameState;

   class GameInputHandler : public IGameInputHandler
   {
   public:
      GameInputHandler( const std::shared_ptr<IGameInputReader>& inputReader,
                        const std::shared_ptr<IGameStateProvider>& stateProvider,
                        const std::shared_ptr<IGameEventAggregator>& eventAggregator );

      void AddInputHandlerForGameState( GameState state,
                                        std::shared_ptr<IGameInputHandler> inputHandler );

      void HandleInput() override;

   private:
      const std::shared_ptr<IGameInputReader>& _inputReader;
      const std::shared_ptr<IGameStateProvider>& _stateProvider;
      const std::shared_ptr<IGameEventAggregator>& _eventAggregator;

      std::map<GameState, std::shared_ptr<IGameInputHandler>> _stateInputHandlers;
   };
}
