#pragma once

#include "IPlayerFactory.h"

namespace ConsoleGame
{
   class GameDefs;

   class PlayerFactory : public IPlayerFactory
   {
   public:
      PlayerFactory( const std::shared_ptr<GameDefs> gameDefs );

      const std::shared_ptr<IPlayer> CreatePlayer() const override;

   private:
      const std::shared_ptr<GameDefs> _gameDefs;
   };
}
