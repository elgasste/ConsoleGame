#pragma once

#include <memory>

#include "IPlayerFactory.h"

namespace ConsoleGame
{
   class PlayerConfig;

   class PlayerFactory : public IPlayerFactory
   {
   public:
      PlayerFactory( const std::shared_ptr<PlayerConfig> config );

      const std::shared_ptr<IPlayer> CreatePlayer() const override;

   private:
      const std::shared_ptr<PlayerConfig> _config;
   };
}
