#include "PlayingStateConsoleRenderer.h"
#include "IConsoleBuffer.h"
#include "ConsoleRenderConfig.h"
#include "GameConfig.h"
#include "IPlayerInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleBuffer> consoleBuffer,
                                                          const shared_ptr<ConsoleRenderConfig> renderConfig,
                                                          const shared_ptr<GameConfig> gameConfig,
                                                          const shared_ptr<IPlayerInfoProvider> playerInfoProvider )
   : _consoleBuffer( consoleBuffer ),
     _renderConfig( renderConfig ),
     _gameConfig( gameConfig ),
     _playerInfoProvider( playerInfoProvider )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleBuffer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleBuffer->SetDefaultForegroundColor( ConsoleColor::White );

   _consoleBuffer->Draw( 2, 1, "Use the direction buttons to move around, or press the A button to quit." );

   DrawArenaFence();

   auto playerX = _playerInfoProvider->GetPlayerXPosition() + _renderConfig->ArenaFenceX + 1;
   auto playerY = _playerInfoProvider->GetPlayerYPosition() + _renderConfig->ArenaFenceY + 1;

   switch ( _playerInfoProvider->GetPlayerDirection() )
   {
      case Direction::Left:
         _consoleBuffer->Draw( playerX, playerY, _renderConfig->PlayerSpriteMap[Direction::Left] );
         break;
      case Direction::Up:
         _consoleBuffer->Draw( playerX, playerY, _renderConfig->PlayerSpriteMap[Direction::Up] );
         break;
      case Direction::Right:
         _consoleBuffer->Draw( playerX - 1, playerY, _renderConfig->PlayerSpriteMap[Direction::Right] );
         break;
      case Direction::Down:
         _consoleBuffer->Draw( playerX, playerY - 1, _renderConfig->PlayerSpriteMap[Direction::Down] );
         break;
   }
}

void PlayingStateConsoleRenderer::DrawArenaFence()
{
   // corners
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY, ',');
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 1, _renderConfig->ArenaFenceY, '.' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '\'' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 1, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '\'' );

   // top and bottom fences
   for ( int left = _renderConfig->ArenaFenceX; left < _gameConfig->ArenaWidth + 2; left++ )
   {
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY, '-' );
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '-' );
   }

   // side fences
   for ( int top = _renderConfig->ArenaFenceY + 1; top < _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1; top++ )
   {
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX, top, '|' );
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 2, top, '|' );
   }
}
