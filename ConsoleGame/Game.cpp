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
   _arenaPlayerPositionY( config->ArenaConfig->PlayerStartY ),
   _playerWasPushedX( false ),
   _playerWasPushedY( false )
{
}

void Game::RunFrame()
{
   if ( _state == GameState::Playing )
   {
      if ( !_playerWasPushedX )
      {
         _player->ApplyFrictionX();
      }
      if ( !_playerWasPushedY )
      {
         _player->ApplyFrictionY();
      }

      MovePlayer();

      _playerWasPushedX = false;
      _playerWasPushedY = false;
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

int Game::GetArenaWidth() const
{
   return _config->ArenaConfig->Width;
}

int Game::GetArenaHeight() const
{
   return _config->ArenaConfig->Height;
}

void Game::PushPlayer( Direction direction )
{
   _player->Push( direction );

   if ( direction == Direction::Left || direction == Direction::Right )
   {
      _playerWasPushedX = true;
   }
   else
   {
      _playerWasPushedY = true;
   }
}

void Game::MovePlayer()
{
   _arenaPlayerPositionX += _player->GetVelocityX();

   if ( _arenaPlayerPositionX < 0 )
   {
      _arenaPlayerPositionX = 0;
      _player->StopX();
   }
   else if ( _arenaPlayerPositionX >= _config->ArenaConfig->Width )
   {
      _arenaPlayerPositionX = _config->ArenaConfig->Width - 1;
      _player->StopX();
   }

   _arenaPlayerPositionY += _player->GetVelocityY();

   if ( _arenaPlayerPositionY < 0 )
   {
      _arenaPlayerPositionY = 0;
      _player->StopY();
   }
   else if ( _arenaPlayerPositionY >= _config->ArenaConfig->Height )
   {
      _arenaPlayerPositionY = _config->ArenaConfig->Height - 1;
      _player->StopY();
   }
}
