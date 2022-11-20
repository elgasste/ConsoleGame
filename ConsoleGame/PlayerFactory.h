#pragma once

#include <memory>

#include "IPlayerFactory.h"

namespace ConsoleGame
{
   class GameConfig;

   class PlayerFactory : public IPlayerFactory
   {
   public:
      PlayerFactory( const std::shared_ptr<GameConfig> config );

      const std::shared_ptr<IPlayer> CreatePlayer() const override;

   private:
      const std::shared_ptr<GameConfig> _config;
   };
}
