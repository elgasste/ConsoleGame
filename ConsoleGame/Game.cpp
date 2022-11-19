#include "Game.h"
#include "GameConfig.h"
#include "PlayerConfig.h"
#include "ArenaConfig.h"
#include "IGameEventAggregator.h"
#include "IPlayerFactory.h"
#include "IPlayer.h"
#include "GameState.h"
#include "GameCommand.h"
#include "GameEvent.h"
#include "Direction.h"
#include "PushPlayerCommandArgs.h"

using namespace std;
using namespace ConsoleGame;

Game::Game( const std::shared_ptr<GameConfig> config,
            const std::shared_ptr<IGameEventAggregator> eventAggregator,
            const std::shared_ptr<IPlayerFactory> playerFactory ) :
   _config( config ),
   _eventAggregator( eventAggregator ),
   _player( playerFactory->CreatePlayer() ),
   _state( GameState::Startup ),
   _arenaPlayerPositionX( config->ArenaConfig->PlayerStartX ),
   _arenaPlayerPositionY( config->ArenaConfig->PlayerStartY )
{
}

void Game::RunFrame()
{
   if ( _state == GameState::Playing )
   {
      // TODO
      // 1) if the player was not pushed Left or Right on this frame, apply friction on X
      // 2) if the player was not pushed Up or Down on this frame, apply friction on Y
      // 3) actually move the player
      // 4) if the player has hit a wall, call _player->StopX() or StopY()
      // 5) reset the "was player pushed" flags
   }
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
      case GameCommand::PushPlayer:
         auto direction = static_pointer_cast<PushPlayerCommandArgs>( args )->Direction;
         PushPlayer( direction );
         break;
   }
}

Direction Game::GetPlayerDirection() const
{
   return _player->GetDirection();
}

void Game::PushPlayer( Direction direction )
{
   switch ( direction )
   {
      case Direction::Left:
         if ( _arenaPlayerPositionX > 0 )
         {
            _arenaPlayerPositionX--;
         }
         break;
      case Direction::Up:
         if ( _arenaPlayerPositionY > 0 )
         {
            _arenaPlayerPositionY--;
         }
         break;
      case Direction::Right:
         if ( _arenaPlayerPositionX < _config->ArenaConfig->Width - 1 )
         {
            _arenaPlayerPositionX++;
         }
         break;
      case Direction::Down:
         if ( _arenaPlayerPositionY < _config->ArenaConfig->Height - 1 )
         {
            _arenaPlayerPositionY++;
         }
         break;
   }
}
