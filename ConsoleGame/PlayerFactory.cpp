#include "PlayerFactory.h"
#include "Player.h"

using namespace std;
using namespace ConsoleGame;

const shared_ptr<IPlayer> PlayerFactory::CreatePlayer() const
{
   return shared_ptr<IPlayer>( new Player() );
}
