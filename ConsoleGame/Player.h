#pragma once

#include <memory>

#include "IPlayer.h"

namespace ConsoleGame
{
   class PlayerConfig;

   class Player : public IPlayer
   {
   public:
      Player( const std::shared_ptr<PlayerConfig> config );

      int GetPositionX() const { return _positionX; }
      int GetPositionY() const { return _positionY; }

      int GetVelocityX() const { return _velocityX; }
      int GetVelocityY() const { return _velocityY; }

   private:
      const std::shared_ptr<PlayerConfig> _config;

      int _positionX;
      int _positionY;

      int _velocityX;
      int _velocityY;
   };
}
