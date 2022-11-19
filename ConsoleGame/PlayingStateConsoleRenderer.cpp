#include "PlayingStateConsoleRenderer.h"
#include "IConsoleBuffer.h"
#include "ConsoleRenderConfig.h"
#include "IPlayerInfoProvider.h"
#include "IArenaInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleBuffer> consoleBuffer,
                                                          const shared_ptr<ConsoleRenderConfig> renderConfig,
                                                          const shared_ptr<IPlayerInfoProvider> playerInfoProvider,
                                                          const shared_ptr<IArenaInfoProvider> arenaInfoProvider ) :
   _consoleBuffer( consoleBuffer ),
   _renderConfig( renderConfig ),
   _playerInfoProvider( playerInfoProvider ),
   _arenaInfoProvider( arenaInfoProvider ),
   _arenaCoordConverterX( renderConfig->ArenaCharWidth / (double)arenaInfoProvider->GetArenaWidth() ),
   _arenaCoordConverterY( renderConfig->ArenaCharHeight / (double)arenaInfoProvider->GetArenaHeight() )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleBuffer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleBuffer->SetDefaultForegroundColor( ConsoleColor::White );

   _consoleBuffer->Draw( 2, 1, "Use the direction buttons to move around, or press the A button to quit." );

   DrawArenaFence();

   auto convertedPlayerX = (short)( _arenaInfoProvider->GetArenaPlayerXPosition() * _arenaCoordConverterX );
   auto convertedPlayerY = (short)( _arenaInfoProvider->GetArenaPlayerYPosition() * _arenaCoordConverterY );

   auto playerX = convertedPlayerX + _renderConfig->ArenaFenceX + 1;
   auto playerY = convertedPlayerY + _renderConfig->ArenaFenceY + 1;

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
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 1, _renderConfig->ArenaFenceY, '.' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '\'' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 1, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '\'' );

   // top and bottom fences
   for ( int left = _renderConfig->ArenaFenceX; left < _renderConfig->ArenaCharWidth + 2; left++ )
   {
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY, '-' );
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '-' );
   }

   // side fences
   for ( int top = _renderConfig->ArenaFenceY + 1; top < _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1; top++ )
   {
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX, top, '|' );
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 2, top, '|' );
   }
}
