#include "PlayerFactory.h"
#include "Player.h"
#include "GameDefs.h"

using namespace std;
using namespace ConsoleGame;

PlayerFactory::PlayerFactory( const shared_ptr<GameDefs> gameDefs ) :
   _gameDefs( gameDefs )
{
}

const shared_ptr<Player> PlayerFactory::CreatePlayer() const
{
   return shared_ptr<Player>( new Player( _gameDefs->PlayerDefs, _gameDefs->FramesPerSecond ) );
}
