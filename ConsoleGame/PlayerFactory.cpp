#include "PlayerFactory.h"
#include "GameDefs.h"
#include "IFrameRateProvider.h"
#include "Player.h"

using namespace std;
using namespace ConsoleGame;

PlayerFactory::PlayerFactory( const shared_ptr<GameDefs> gameDefs,
                              const shared_ptr<IFrameRateProvider> frameRateProvider ) :
   _gameDefs( gameDefs ),
   _frameRateProvider( frameRateProvider )
{
}

const shared_ptr<Player> PlayerFactory::CreatePlayer() const
{
   return shared_ptr<Player>( new Player( _gameDefs->PlayerDefs, _frameRateProvider ) );
}
