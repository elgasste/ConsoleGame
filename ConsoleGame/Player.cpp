#include <algorithm>

#include "Player.h"
#include "PlayerConfig.h"

using namespace std;
using namespace ConsoleGame;

Player::Player( const shared_ptr<PlayerConfig> config,
                int framesPerSecond ) :
   _config( config ),
   _velocityX( _config->StartVelocityX ),
   _velocityY( _config->StartVelocityY ),
   _velocityDelta( _config->AccelerationPerSecond / framesPerSecond ),
   _direction( _config->StartDirection )
{
}

void Player::Push( Direction direction )
{
   _direction = direction;

   switch ( direction )
   {
   case Direction::Left:
      _velocityX -= _velocityDelta;
      break;
   case Direction::UpLeft:
      _velocityX -= _velocityDelta;
      _velocityY -= _velocityDelta;
      break;
   case Direction::Up:
      _velocityY -= _velocityDelta;
      break;
   case Direction::UpRight:
      _velocityX += _velocityDelta;
      _velocityY -= _velocityDelta;
      break;
   case Direction::Right:
      _velocityX += _velocityDelta;
      break;
   case Direction::DownRight:
      _velocityX += _velocityDelta;
      _velocityY += _velocityDelta;
      break;
   case Direction::Down:
      _velocityY += _velocityDelta;
      break;
   case Direction::DownLeft:
      _velocityX -= _velocityDelta;
      _velocityY += _velocityDelta;
      break;
   }

   ClampVelocity();
}

void Player::ApplyFrictionX()
{
   if ( _velocityX < 0. )
   {
      _velocityX = min( _velocityX + _velocityDelta, 0. );
   }
   else if ( _velocityX > 0. )
   {
      _velocityX = max( _velocityX - _velocityDelta, 0. );
   }
}

void Player::ApplyFrictionY()
{
   if ( _velocityY < 0. )
   {
      _velocityY = min( _velocityY + _velocityDelta, 0. );
   }
   else if ( _velocityY > 0. )
   {
      _velocityY = max( _velocityY - _velocityDelta, 0. );
   }
}

void Player::StopX()
{
   _velocityX = 0.;
}

void Player::StopY()
{
   _velocityY = 0.;
}

void Player::ClampVelocity()
{
   if ( _velocityX < -( _config->MaxVelocity ) )
   {
      _velocityX = -( _config->MaxVelocity );
   }
   else if ( _velocityX > _config->MaxVelocity )
   {
      _velocityX = _config->MaxVelocity;
   }

   if ( _velocityY < -( _config->MaxVelocity ) )
   {
      _velocityY = -( _config->MaxVelocity );
   }
   else if ( _velocityY > _config->MaxVelocity )
   {
      _velocityY = _config->MaxVelocity;
   }
}
