#include "Game.h"
#include "GameConfig.h"
#include "ArenaDefs.h"
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
   _arenaPlayerPositionX( config->ArenaDefs->PlayerStartX ),
   _arenaPlayerPositionY( config->ArenaDefs->PlayerStartY ),
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

bool Game::IsPlayerMoving() const
{
   return _player->GetVelocityX() != 0. || _player->GetVelocityY() != 0.;
}

double Game::GetArenaWidth() const
{
   return _config->ArenaDefs->Width;
}

double Game::GetArenaHeight() const
{
   return _config->ArenaDefs->Height;
}

void Game::PushPlayer( Direction direction )
{
   _player->Push( direction );

   if ( direction != Direction::Up && direction != Direction::Down )
   {
      _playerWasPushedX = true;
   }
   if ( direction != Direction::Left && direction != Direction::Right )
   {
      _playerWasPushedY = true;
   }
}

void Game::MovePlayer()
{
   _arenaPlayerPositionX += ( _player->GetVelocityX() / _config->FramesPerSecond );

   if ( _arenaPlayerPositionX < 0. )
   {
      _arenaPlayerPositionX = 0.;
      _player->StopX();
   }
   else if ( _arenaPlayerPositionX >= _config->ArenaDefs->Width )
   {
      _arenaPlayerPositionX = _config->ArenaDefs->Width - 1.;
      _player->StopX();
   }

   _arenaPlayerPositionY += ( _player->GetVelocityY() / _config->FramesPerSecond );

   if ( _arenaPlayerPositionY < 0. )
   {
      _arenaPlayerPositionY = 0.;
      _player->StopY();
   }
   else if ( _arenaPlayerPositionY >= _config->ArenaDefs->Height )
   {
      _arenaPlayerPositionY = _config->ArenaDefs->Height - 1.;
      _player->StopY();
   }
}
