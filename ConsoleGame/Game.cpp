#include "Game.h"
#include "GameState.h"
#include "GameCommand.h"
#include "IGameEventAggregator.h"
#include "GameEvent.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<IGameEventAggregator>& eventAggregator )
   : _eventAggregator( eventAggregator ),
     _state( GameState::Startup )
{
}

void Game::ExecuteCommand( GameCommand command )
{
   switch ( command )
   {
      case GameCommand::Start:
         _state = GameState::Playing;
         break;
      case GameCommand::Quit:
         _eventAggregator->RaiseEvent( GameEvent::Shutdown );
         break;
   }
}
