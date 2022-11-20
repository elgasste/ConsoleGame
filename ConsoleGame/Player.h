#pragma once

#include <memory>

#include "IPlayer.h"

namespace ConsoleGame
{
   class PlayerConfig;

   class Player : public IPlayer
   {
   public:
      Player( const std::shared_ptr<PlayerConfig> config,
              int framesPerSecond );

      void Push( Direction direction ) override;
      void ApplyFrictionX() override;
      void ApplyFrictionY() override;
      void StopX() override;
      void StopY() override;

      double GetVelocityX() const override { return _velocityX; }
      double GetVelocityY() const override { return _velocityY; }

      Direction GetDirection() const override { return _direction; }

   private:
      void ClampVelocity();

   private:
      const std::shared_ptr<PlayerConfig> _config;

      double _velocityX;
      double _velocityY;

      double _velocityDelta;

      Direction _direction;
   };
}
