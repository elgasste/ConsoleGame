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

      int GetPositionX() const override { return _positionX; }
      int GetPositionY() const override { return _positionY; }

      int GetVelocityX() const override { return _velocityX; }
      int GetVelocityY() const override { return _velocityY; }

      Direction GetDirection() const override { return _direction; }

   private:
      const std::shared_ptr<PlayerConfig> _config;

      int _positionX;
      int _positionY;

      int _velocityX;
      int _velocityY;

      Direction _direction;
   };
}
