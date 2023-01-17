#pragma once

#include <memory>

#include "Direction.h"

namespace ConsoleGame
{
   class PlayerDefs;
   class IFrameRateProvider;

   class Player
   {
   public:
      Player();
      Player( const std::shared_ptr<PlayerDefs> playerDefs,
              const std::shared_ptr<IFrameRateProvider> frameRateProvider );

      virtual void Push( Direction direction );
      virtual void ApplyFrictionX();
      virtual void ApplyFrictionY();
      virtual void StopX();
      virtual void StopY();

      virtual float GetVelocityX() const { return _velocityX; }
      virtual float GetVelocityY() const { return _velocityY; }

      virtual Direction GetDirection() const { return _direction; }

   private:
      void ClampVelocity();

   private:
      const std::shared_ptr<PlayerDefs> _playerDefs;
      const std::shared_ptr<IFrameRateProvider> _frameRateProvider;

      float _velocityX;
      float _velocityY;

      Direction _direction;
   };
}
