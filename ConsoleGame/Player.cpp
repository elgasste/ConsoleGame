#include <algorithm>

#include "Player.h"
#include "PlayerDefs.h"

using namespace std;
using namespace ConsoleGame;

Player::Player( const shared_ptr<PlayerDefs> playerDefs,
                int framesPerSecond ) :
   _playerDefs( playerDefs ),
   _velocityX( _playerDefs->StartVelocityX ),
   _velocityY( _playerDefs->StartVelocityY ),
   _velocityDelta( _playerDefs->AccelerationPerSecond / framesPerSecond ),
   _direction( _playerDefs->StartDirection )
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
   if ( _velocityX < 0 )
   {
      _velocityX = min( _velocityX + _velocityDelta, 0.0f );
   }
   else if ( _velocityX > 0 )
   {
      _velocityX = max( _velocityX - _velocityDelta, 0.0f );
   }
}

void Player::ApplyFrictionY()
{
   if ( _velocityY < 0 )
   {
      _velocityY = min( _velocityY + _velocityDelta, 0.0f );
   }
   else if ( _velocityY > 0 )
   {
      _velocityY = max( _velocityY - _velocityDelta, 0.0f );
   }
}

void Player::StopX()
{
   _velocityX = 0;
}

void Player::StopY()
{
   _velocityY = 0;
}

void Player::ClampVelocity()
{
   if ( _velocityX < -( _playerDefs->MaxVelocity ) )
   {
      _velocityX = -( _playerDefs->MaxVelocity );
   }
   else if ( _velocityX > _playerDefs->MaxVelocity )
   {
      _velocityX = _playerDefs->MaxVelocity;
   }

   if ( _velocityY < -( _playerDefs->MaxVelocity ) )
   {
      _velocityY = -( _playerDefs->MaxVelocity );
   }
   else if ( _velocityY > _playerDefs->MaxVelocity )
   {
      _velocityY = _playerDefs->MaxVelocity;
   }
}
