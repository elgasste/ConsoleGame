#pragma once

#include "IPlayerFactory.h"

namespace ConsoleGame
{
   class PlayerFactory : public IPlayerFactory
   {
   public:
      const std::shared_ptr<IPlayer> CreatePlayer() const override;
   };
}
