#include "PlayerFactory.h"
#include "Player.h"
#include "GameConfig.h"

using namespace std;
using namespace ConsoleGame;

PlayerFactory::PlayerFactory( const shared_ptr<GameConfig> config ) :
   _config( config )
{
}

const shared_ptr<IPlayer> PlayerFactory::CreatePlayer() const
{
   return shared_ptr<IPlayer>( new Player( _config->PlayerDefs, _config->FramesPerSecond ) );
}
