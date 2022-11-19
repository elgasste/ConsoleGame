#include <algorithm>

#include "Player.h"
#include "PlayerConfig.h"

using namespace std;
using namespace ConsoleGame;

Player::Player( const shared_ptr<PlayerConfig> config ) :
   _config( config ),
   _velocityX( config->StartVelocityX ),
   _velocityY( config->StartVelocityY ),
   _direction( config->StartDirection )
{
}

void Player::Push( Direction direction )
{
   _direction = direction;

   switch ( direction )
   {
   case Direction::Left:
      _velocityX -= _config->VelocityDeltaX;
      break;
   case Direction::Right:
      _velocityX += _config->VelocityDeltaX;
      break;
   case Direction::Up:
      _velocityY -= _config->VelocityDeltaY;
      break;
   case Direction::Down:
      _velocityY += _config->VelocityDeltaY;
      break;
   }

   ClampVelocity();
}

void Player::ApplyFrictionX()
{
   if ( _velocityX < 0 )
   {
      _velocityX = min( _velocityX + _config->VelocityDeltaX, 0 );
   }
   else if ( _velocityX > 0 )
   {
      _velocityX = max( _velocityX - _config->VelocityDeltaX, 0 );
   }
}

void Player::ApplyFrictionY()
{
   if ( _velocityY < 0 )
   {
      _velocityY = min( _velocityY + _config->VelocityDeltaY, 0 );
   }
   else if ( _velocityY > 0 )
   {
      _velocityY = max( _velocityY - _config->VelocityDeltaY, 0 );
   }
}

void Player::ClampVelocity()
{
   if ( _velocityX < -( _config->MaxVelocityX ) )
   {
      _velocityX = -( _config->MaxVelocityX );
   }
   else if ( _velocityX > _config->MaxVelocityX )
   {
      _velocityX = _config->MaxVelocityX;
   }

   if ( _velocityY < -( _config->MaxVelocityY ) )
   {
      _velocityY = -( _config->MaxVelocityY );
   }
   else if ( _velocityY > _config->MaxVelocityY )
   {
      _velocityY = _config->MaxVelocityY;
   }
}
