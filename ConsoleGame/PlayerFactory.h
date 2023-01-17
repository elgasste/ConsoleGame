#pragma once

#include <memory>

namespace ConsoleGame
{
   class GameDefs;
   class IFrameRateProvider;
   class Player;

   class PlayerFactory
   {
   public:
      PlayerFactory() { }
      PlayerFactory( const std::shared_ptr<GameDefs> gameDefs,
                     const std::shared_ptr<IFrameRateProvider> frameRateProvider );

      virtual const std::shared_ptr<Player> CreatePlayer() const;

   private:
      const std::shared_ptr<GameDefs> _gameDefs;
      const std::shared_ptr<IFrameRateProvider> _frameRateProvider;
   };
}
