#include "Game.h"
#include "GameState.h"
#include "GameCommand.h"
#include "IGameEventAggregator.h"
#include "GameEvent.h"
#include "Direction.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<IGameEventAggregator>& eventAggregator )
   : _eventAggregator( eventAggregator ),
     _state( GameState::Startup ),
     _playerDirection( Direction::Right ),
     _playerPositionX( 0 ),
     _playerPositionY( 0 )
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
      case GameCommand::MovePlayerLeft:
         _playerPositionX--;
         _playerDirection = Direction::Left;
         break;
      case GameCommand::MovePlayerUp:
         _playerPositionY--;
         _playerDirection = Direction::Up;
         break;
      case GameCommand::MovePlayerRight:
         _playerPositionX++;
         _playerDirection = Direction::Right;
         break;
      case GameCommand::MovePlayerDown:
         _playerPositionY++;
         _playerDirection = Direction::Down;
         break;
   }
}
