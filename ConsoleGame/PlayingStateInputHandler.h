#pragma once

#include <memory>

#include "IGameInputHandler.h"

namespace ConsoleGame
{
   class IGameInputReader;
   class IGameEventAggregator;

   class PlayingStateInputHandler : public IGameInputHandler
   {
   public:
      PlayingStateInputHandler( const std::shared_ptr<IGameInputReader>& inputReader,
                                const std::shared_ptr<IGameEventAggregator>& eventAggregator );

      void HandleInput() override;

   private:
      const std::shared_ptr<IGameInputReader>& _inputReader;
      const std::shared_ptr<IGameEventAggregator>& _eventAggregator;
   };
}