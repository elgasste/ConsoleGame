#include "Player.h"
#include "PlayerConfig.h"

using namespace std;
using namespace ConsoleGame;

Player::Player( const shared_ptr<PlayerConfig> config )
   : _config( config ),
     _positionX( config->StartPositionX ),
     _positionY( config->StartPositionY ),
     _velocityX( config->StartVelocityX ),
     _velocityY( config->StartVelocityY )
{
}
