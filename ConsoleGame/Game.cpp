#include "Game.h"
#include "GameConfig.h"
#include "GameState.h"
#include "GameCommand.h"
#include "IGameEventAggregator.h"
#include "GameEvent.h"
#include "Direction.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<GameConfig>& config,
            const std::shared_ptr<IGameEventAggregator>& eventAggregator )
   : _config( config ),
     _eventAggregator( eventAggregator ),
     _state( GameState::Startup ),
     _playerDirection( config->PlayerStartDirection ),
     _playerPositionX( config->PlayerStartX ),
     _playerPositionY( config->PlayerStartY )
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
         if ( _playerPositionX > 0 )
         {
            _playerPositionX--;
         }
         _playerDirection = Direction::Left;
         break;
      case GameCommand::MovePlayerUp:
         if ( _playerPositionY > 0 )
         {
            _playerPositionY--;
         }
         _playerDirection = Direction::Up;
         break;
      case GameCommand::MovePlayerRight:
         if ( _playerPositionX < _config->ArenaWidth - 1 )
         {
            _playerPositionX++;
         }
         _playerDirection = Direction::Right;
         break;
      case GameCommand::MovePlayerDown:
         if ( _playerPositionY < _config->ArenaHeight - 1 )
         {
            _playerPositionY++;
         }
         _playerDirection = Direction::Down;
         break;
   }
}
