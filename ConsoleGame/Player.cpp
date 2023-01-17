#include <algorithm>

#include "Player.h"
#include "PlayerDefs.h"
#include "IFrameRateProvider.h"

using namespace std;
using namespace ConsoleGame;

Player::Player() :
   _velocityX( 0 ),
   _velocityY( 0 ),
   _direction( (Direction)0 )
{
}

Player::Player( const shared_ptr<PlayerDefs> playerDefs,
                const shared_ptr<IFrameRateProvider> frameRateProvider ) :
   _playerDefs( playerDefs ),
   _frameRateProvider( frameRateProvider ),
   _velocityX( _playerDefs->StartVelocityX ),
   _velocityY( _playerDefs->StartVelocityY ),
   _direction( _playerDefs->StartDirection )
{
}

void Player::Push( Direction direction )
{
   auto velocityDelta = _playerDefs->AccelerationPerSecond * _frameRateProvider->GetFrameSeconds();
   _direction = direction;

   switch ( direction )
   {
   case Direction::Left:
      _velocityX -= velocityDelta;
      break;
   case Direction::UpLeft:
      _velocityX -= velocityDelta;
      _velocityY -= velocityDelta;
      break;
   case Direction::Up:
      _velocityY -= velocityDelta;
      break;
   case Direction::UpRight:
      _velocityX += velocityDelta;
      _velocityY -= velocityDelta;
      break;
   case Direction::Right:
      _velocityX += velocityDelta;
      break;
   case Direction::DownRight:
      _velocityX += velocityDelta;
      _velocityY += velocityDelta;
      break;
   case Direction::Down:
      _velocityY += velocityDelta;
      break;
   case Direction::DownLeft:
      _velocityX -= velocityDelta;
      _velocityY += velocityDelta;
      break;
   }

   ClampVelocity();
}

void Player::ApplyFrictionX()
{
   auto velocityDelta = _playerDefs->AccelerationPerSecond * _frameRateProvider->GetFrameSeconds();

   if ( _velocityX < 0 )
   {
      _velocityX = min( _velocityX + velocityDelta, 0.0f );
   }
   else if ( _velocityX > 0 )
   {
      _velocityX = max( _velocityX - velocityDelta, 0.0f );
   }
}

void Player::ApplyFrictionY()
{
   auto velocityDelta = _playerDefs->AccelerationPerSecond * _frameRateProvider->GetFrameSeconds();

   if ( _velocityY < 0 )
   {
      _velocityY = min( _velocityY + velocityDelta, 0.0f );
   }
   else if ( _velocityY > 0 )
   {
      _velocityY = max( _velocityY - velocityDelta, 0.0f );
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
