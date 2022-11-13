#include "Game.h"
#include "GameConfig.h"
#include "IGameEventAggregator.h"
#include "GameState.h"
#include "GameCommand.h"
#include "GameEvent.h"
#include "Direction.h"
#include "MovePlayerCommandArgs.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<GameConfig> config,
            const std::shared_ptr<IGameEventAggregator> eventAggregator )
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
   ExecuteCommand( command, nullptr );
}

void Game::ExecuteCommand( GameCommand command, const shared_ptr<GameCommandArgs> args )
{
   switch ( command )
   {
      case GameCommand::Start:
         _state = GameState::Playing;
         break;
      case GameCommand::Quit:
         _eventAggregator->RaiseEvent( GameEvent::Shutdown );
         break;
      case GameCommand::MovePlayer:
         auto direction = static_pointer_cast<MovePlayerCommandArgs>( args )->Direction;
         MovePlayer( direction );
         break;
   }
}

void Game::MovePlayer( Direction direction )
{
   switch ( direction )
   {
      case Direction::Left:
         if ( _playerPositionX > 0 )
         {
            _playerPositionX--;
         }
         _playerDirection = Direction::Left;
         break;
      case Direction::Up:
         if ( _playerPositionY > 0 )
         {
            _playerPositionY--;
         }
         _playerDirection = Direction::Up;
         break;
      case Direction::Right:
         if ( _playerPositionX < _config->ArenaWidth - 1 )
         {
            _playerPositionX++;
         }
         _playerDirection = Direction::Right;
         break;
      case Direction::Down:
         if ( _playerPositionY < _config->ArenaHeight - 1 )
         {
            _playerPositionY++;
         }
         _playerDirection = Direction::Down;
         break;
   }
}
