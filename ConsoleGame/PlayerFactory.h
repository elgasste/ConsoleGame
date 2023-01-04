#pragma once

#include <memory>

namespace ConsoleGame
{
   class GameDefs;
   class Player;

   class PlayerFactory
   {
   public:
      PlayerFactory() { }
      PlayerFactory( const std::shared_ptr<GameDefs> gameDefs );

      virtual const std::shared_ptr<Player> CreatePlayer() const;

   private:
      const std::shared_ptr<GameDefs> _gameDefs;
   };
}
